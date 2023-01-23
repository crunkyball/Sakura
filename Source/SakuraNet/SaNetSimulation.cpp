/*************************************************************
Sakura Game Framework : SaNetSimulation.cpp
Author: Darrell Blake
*************************************************************/

#include "SaNetSimulation.h"

#ifdef NET_SIMULATION_ENABLED

#include "SaNetConnection.h"
#include <Sakura/SaTime.h>

using namespace SakuraNet;
using namespace Sakura;

SaNetSimulation::SaNetSimulation()
{
    for (uint32_t i = 0; i < METHOD_MAX; i++)
    {
        m_methods[i] = NULL;
    }
}

SaNetSimulation::~SaNetSimulation()
{
    Clean();
}

SaNetSimMethod* SaNetSimulation::CreateMethod(ESimulationMethod eMethod)
{
    SaNetSimMethod* pMethod = NULL;

    switch(eMethod)
    {
        case METHOD_DROP_PACKETS:
            pMethod = new SaNetSimMethod_DropPackets();
            break;
        case METHOD_DELAY_PACKETS:
            pMethod = new SaNetSimMethod_DelayPackets();
            break;
        default:
            SA_FAIL("Unsupported method.");
    }

    return pMethod;
}

void SaNetSimulation::AddMethod(SaNetSimMethod* pMethod)
{
    if (pMethod)
    {
        SA_ASSERT(m_methods[pMethod->GetMethodType()] == NULL, "Method already exists.");

        m_methods[pMethod->GetMethodType()] = pMethod;
    }
}

void SaNetSimulation::Clean()
{
    for (uint32_t i = 0; i < METHOD_MAX; i++)
    {
        if (m_methods[i] != NULL)
        {
            delete m_methods[i];
            m_methods[i] = NULL;
        }
    }
}

bool SaNetSimulation::SendPacket(SaNetSocket& rSocket, SaNetAddress& rSendTo, SaNetPacket& rPacket)
{
    for (uint32_t i = 0; i < METHOD_MAX; i++)
    {
        if (m_methods[i] != NULL)
        {
            if (m_methods[i]->HandleOutgoingPacket(rSendTo, rPacket) == false)
            {
                //One of the methods wants us to ignore this packet so 
                //pretend it was sent fine.
                return true;
            }
        }
    }

    //Otherwise just send it like normal.
    return rSocket.Send(rSendTo, rPacket);
}

int32_t SaNetSimulation::ReceivePacket(SaNetSocket& rSocket, SaNetAddress& rSender, SaNetPacket& rPacket)
{
    for (uint32_t i = 0; i < METHOD_MAX; i++)
    {
        if (m_methods[i] != NULL)
        {
            if (m_methods[i]->HandleIncomingPacket(rPacket) == false)
            {
                //One of the methods wants us to ignore this packet so
                //pretend it doesn't exist.
                return 0;
            }
        }
    }

    return rSocket.Receive(rSender, rPacket);
}

void SaNetSimulation::Update(SaNetSocket& rSocket, uint32_t uDeltaTime)
{
    for (uint32_t i = 0; i < METHOD_MAX; i++)
    {
        if (m_methods[i] != NULL)
        {
            m_methods[i]->Update(rSocket, uDeltaTime);
        }
    }
}

///////////////////////////////////////////////////////////////////////

SaNetSimMethod::SaNetSimMethod(SaNetSimulation::ESimulationMethod eMethodType) :
    m_rand(SaTime::GetTimeMilliseconds())
{
    m_eMethodType = eMethodType;
}

///////////////////////////////////////////////////////////////////////

SaNetSimMethod_DropPackets::SaNetSimMethod_DropPackets() : SaNetSimMethod(SaNetSimulation::METHOD_DROP_PACKETS),
m_uDropPercentage(0)
{
}

bool SaNetSimMethod_DropPackets::HandleOutgoingPacket(SaNetAddress& rSendTo, SaNetPacket& rPacket)
{
    if (m_uDropPercentage > 0 && m_rand.GetUint32(100) < m_uDropPercentage)
    {
        return false;
    }

    return true;
}

///////////////////////////////////////////////////////////////////////

SaNetSimMethod_DelayPackets::SaNetSimMethod_DelayPackets() : SaNetSimMethod(SaNetSimulation::METHOD_DELAY_PACKETS),
m_iDelayTime(0)
{
    for (int i = 0; i < MAX_DELAYED_PACKETS; i++)
    {
        m_delayedPackets[i].delayTime = 0;
    }

    m_pDelayedPacketItr = &m_delayedPackets[0];
}

bool SaNetSimMethod_DelayPackets::HandleOutgoingPacket(SaNetAddress& rSendTo, SaNetPacket& rPacket)
{
    SA_ASSERT(m_pDelayedPacketItr->delayTime == 0, "Too many packets being sent during delay?");

    m_pDelayedPacketItr->delayTime = m_iDelayTime;
    m_pDelayedPacketItr->packet = rPacket;
    m_pDelayedPacketItr->sendTo = rSendTo;

    //Increment the iterator.
    if (m_pDelayedPacketItr == &m_delayedPackets[MAX_DELAYED_PACKETS - 1])
    {
        m_pDelayedPacketItr = &m_delayedPackets[0];
    }
    else
    {
        m_pDelayedPacketItr++;
    }

    return false;
}

void SaNetSimMethod_DelayPackets::Update(SaNetSocket& rSocket, uint32_t uDeltaTime)
{
    for (uint32_t i = 0; i < MAX_DELAYED_PACKETS; i++)
    {
        DelayedPacket* pDelayedPacket = &m_delayedPackets[i];

        if (pDelayedPacket->delayTime > 0)
        {
            pDelayedPacket->delayTime -= uDeltaTime;

            //Delay finished. Handle packet.
            if (pDelayedPacket->delayTime <= 0)
            {
                pDelayedPacket->delayTime = 0;
                rSocket.Send(pDelayedPacket->sendTo, pDelayedPacket->packet);
            }
        }
    }
}

#endif
