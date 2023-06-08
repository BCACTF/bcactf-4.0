import bpy

def encode(obj, message):
    # Ensure the object is a mesh
    if obj.type != 'MESH':
        print('Object is not a mesh.')
        return

    # Ensure the mesh has enough vertices for the message
    if len(obj.data.vertices) < len(message):
        print('Mesh does not have enough vertices for the message.')
        return

    # Iterate over each character in the message
    for i, char in enumerate(message):
        # Change the z-coordinate according to the ASCII value of the character
        obj.data.vertices[i].co.z += ord(char) / 10000.0

def decode(obj, original_obj):
    # Ensure the objects are meshes
    if obj.type != 'MESH' or original_obj.type != 'MESH':
        print('Object is not a mesh.')
        return

    # Ensure the meshes have the same number of vertices
    if len(obj.data.vertices) != len(original_obj.data.vertices):
        print('Meshes do not have the same number of vertices.')
        return

    # Start with an empty message
    message = ''

    # Iterate over each vertex
    for i in range(len(obj.data.vertices)):
        # Calculate the difference in the z-coordinate
        diff = obj.data.vertices[i].co.z - original_obj.data.vertices[i].co.z

        # Convert the difference to an ASCII value and add the corresponding character to the message
        message += chr(int(round(diff * 10000.0)))

    return message

# Get the active object
obj = bpy.context.object

# Get the original object (you'll need to replace this with the actual original object)
original_obj = bpy.context.scene.objects['Original']

# Encode a message
encode(obj, 'bcactf{b13nD3R_m0nK3Y_5hifHJf}')

# Decode the message
print(decode(obj, original_obj))
