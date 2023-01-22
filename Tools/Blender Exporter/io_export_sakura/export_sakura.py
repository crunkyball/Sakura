import struct

class Vertex:
    __slots__ = "position", "normal"
    
    def __init__(self, position, normal):
        self.position = position
        self.normal = normal

class Triangle:
    __slots__ = "vertIndices"
    
    def __init__(self, vertIndices):
        self.vertIndices = vertIndices

class Material:
    diffuseColour = []
    
    def __init__(self, diffuseColour=(0.0,0.0,0.0)):
        self.diffuseColour = diffuseColour

class SakFile:
    FILE_VERSION = 4
    vertices = []
    triangles = []
    material = None
    
    def write(self, file):
        
        #Write the header first.
        file.write(struct.pack("I", self.FILE_VERSION))
        
        numVertices = len(self.vertices)
        file.write(struct.pack("I", numVertices))
        
        numTriangles = len(self.triangles)
        file.write(struct.pack("I", numTriangles))
        
        #Write the vertex data.
        for vert in self.vertices:
            file.write(struct.pack("fff", vert.position[0], vert.position[1], vert.position[2]))
            file.write(struct.pack("fff", vert.normal[0], vert.normal[1], vert.normal[2]))
        
        #Write the triangle data.
        for tri in self.triangles:
            file.write(struct.pack("III", tri.vertIndices[0], tri.vertIndices[1], tri.vertIndices[2]))
        
        #Write the material data. We currently only support one material.
        if self.material:
            file.write(struct.pack("fff", self.material.diffuseColour[0], self.material.diffuseColour[1], self.material.diffuseColour[2]))
        else:
            raise Exception("Invalid material!")

#This function swaps the Y and Z elements of each vertex (as Blender uses Z for up). 
#However, this effectively changes the winding order so we also swap the second and  
#third vertex indices in the function below to correct this.            
def create_vertex(vertex):
    position = (vertex.co[0], vertex.co[2], vertex.co[1])
    normal = (vertex.normal[0], vertex.normal[2], vertex.normal[1])
    myVertex = Vertex(position, normal)
    return myVertex
    
def create_triangle(vertIndices):
    triangle = Triangle((vertIndices[0], vertIndices[2], vertIndices[1]))
    return triangle

def extract_vertices(mesh):
    vertices = []
    
    for vertNum, vert in enumerate(mesh.vertices):
        vertex = create_vertex(vert)
        vertices.append(vertex)
    
    return vertices

def extract_triangles(mesh):
    triangles = []
    
    mesh.calc_loop_triangles()
    
    for faceNum, face in enumerate(mesh.loop_triangles):
    
        if len(face.vertices) == 3:
            triangle = create_triangle((face.vertices[0], face.vertices[1], face.vertices[2]))
            triangles.append(triangle)
            
        elif len(face.vertices) == 4:
            triangle1 = create_triangle((face.vertices[0], face.vertices[1], face.vertices[2]))
            triangle2 = create_triangle((face.vertices[0], face.vertices[2], face.vertices[3]))
            triangles.append(triangle1)
            triangles.append(triangle2)
            
        else:
            raise Exception("Unsupported number of vertices!")
            
    return triangles

def extract_material(mesh):   
    material = None
    
    matIdx = -1
    
    if len(mesh.materials) > 0:
        #We currently only support the exporting of one material.
        for faceNum, face in enumerate(mesh.loop_triangles):
            if (matIdx != -1 and matIdx != face.material_index):
                raise Exception("Object must use only one material.")
            matIdx = face.material_index
    
        if len(mesh.materials) < matIdx:
            raise Exception("Material index too small.")
        else:
            material = Material(mesh.materials[matIdx].diffuse_color)
    else:
        raise Exception("No materials found. One is required.")
        
    return material

def export_model(object, filepath):
    """Save the model to an .sak file."""
    
    import time
    
    timeStart = time.time()
    
    file = open(filepath, "bw")
        
    sakFile = SakFile()
    sakFile.vertices = extract_vertices(object.data)
    sakFile.triangles = extract_triangles(object.data)
    sakFile.material = extract_material(object.data)
    
    sakFile.write(file)
    
    file.close()
    
    timeEnd = time.time()
    
    print("Export finished! (Took %.2fs)" % (timeEnd - timeStart))
    return {"FINISHED"}
