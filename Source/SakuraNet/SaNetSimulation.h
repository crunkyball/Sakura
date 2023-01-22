/*************************************************************
Sakura Game Framework : SaNetSimulation.h
Author: Darrell Blake
*************************************************************/

#ifndef _SA_NET_SIMULATION_H
#define _SA_NET_SIMULATION_H

#define NET_SIMULATION_ENABLED

#ifdef NET_SIMULATION_ENABLED

#include <Sakura/SaCore.h>
#include "SaNetAddress.h"
#include "SaNetPacket.h"
#include "SaNetSocket.h"
#include <Sakura/SaRand.h>

using namespace Sakura;

namespace SakuraNet
{
    class SaNetSimMethod;

    class SaNetSimulation
    {
    public:
        enum ESimulationMethod
        {
            METHOD_DROP_PACKETS = 0,
            METHOD_DELAY_PACKETS,
            METHOD_MAX
        };

        SaNetSimulation();
        ~SaNetSimulation();

        SaNetSimMethod* CreateMethod(ESimulationMethod eMethod);
        void AddMethod(SaNetSimMethod* pMethod);

        bool SendPacket(SaNetSocket& rSocket, SaNetAddress& rSendTo, SaNetPacket& rPacket);
        int32_t ReceivePacket(SaNetSocket& rSocket, SaNetAddress& rSender, SaNetPacket& rPacket);

        void Update(SaNetSocket& rSocket, uint32_t uDeltaTime);

    private:
        SaNetSimMethod* m_methods[METHOD_MAX];

        void Clean();
    };

    ///////////////////////////////////////////////////////////////////////

    class SaNetSimMethod
    {
    public:
        SaNetSimMethod(SaNetSimulation::ESimulationMethod eMethodType);

        //Unless the inherited classes override these everything 
        //will just work as if there was no simulation.
        virtual bool HandleOutgoingPacket(SaNetAddress& rSendTo, SaNetPacket& rPacket) { return true; }
        virtual bool HandleIncomingPacket(SaNetPacket& rPacket) { return true; }
        
        virtual void Update(SaNetSocket& rSocket, uint32_t uDeltaTime) {};

        SaNetSimulation::ESimulationMethod GetMethodType() { return m_eMethodType; }

    protected:
        SaNetSimulation::ESimulationMethod  m_eMethodType;
        SaRand m_rand;

    private:

    };

    ///////////////////////////////////////////////////////////////////////

    class SaNetSimMethod_DropPackets : public SaNetSimMethod
    {
    public:
        SaNetSimMethod_DropPackets();

        virtual bool    HandleOutgoingPacket(SaNetAddress& rSendTo, SaNetPacket& rPacket);

        void            SetDropPercentage(uint8_t uDropPercentage) { m_uDropPercentage = uDropPercentage; }

    private:
        uint8_t m_uDropPercentage;
    };

    ///////////////////////////////////////////////////////////////////////

    class SaNetSimMethod_DelayPackets : public SaNetSimMethod
    {
    public:
        SaNetSimMethod_DelayPackets();

        virtual bool    HandleOutgoingPacket(SaNetAddress& rSendTo, SaNetPacket& rPacket);
        virtual void    Update(SaNetSocket& rSocket, uint32_t uDeltaTime);

        void            SetDelayTime(int32_t iDelayTime) { m_iDelayTime = iDelayTime; }

    private:

        static const uint32_t MAX_DELAYED_PACKETS = 128;

        struct DelayedPacket
        {
            SaNetPacket packet;
            SaNetAddress sendTo;
            int32_t delayTime;
        };

        DelayedPacket m_delayedPackets[MAX_DELAYED_PACKETS];
        DelayedPacket* m_pDelayedPacketItr;

        int32_t m_iDelayTime;
    };
}

#endif //NET_SIMULATION_ENABLED

#endif //_SA_NET_SIMULATION_H
