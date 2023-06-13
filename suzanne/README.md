# Suzanne (Foren, 150 points) 

If you look at the two models separately, they look pretty much identical. However, looking at them together reveals slight differences in some of the vertices.

![modeldiff](https://github.com/BCACTF/bcactf-4.0/assets/43799189/00ba2c41-5a3f-44d2-8056-52156676b5dc)

These differences are too small to analyze by hand, but we can write a script to do it for us. Here is a Blender Python script (Scripting > New) to print out all the vertices that are different between the two models:

```python
import bpy

original = bpy.data.objects['Original']
modified = bpy.data.objects['Modified']
for i in range(len(original.data.vertices)):
    if original.data.vertices[i].co != modified.data.vertices[i].co:
        print(original.data.vertices[i].co, "\n",  modified.data.vertices[i].co, "\n")
```

And here is the output:
```
<Vector (0.4375, -0.7656, 0.1641)>
 <Vector (0.4375, -0.7656, 0.1739)>

<Vector (-0.4375, -0.7656, 0.1641)>
 <Vector (-0.4375, -0.7656, 0.1740)>

<Vector (0.5000, -0.6875, 0.0938)>
 <Vector (0.5000, -0.6875, 0.1035)>

...
```


We can see that the z-coordinates of the verticies are different, the modified model seems to have them shifted up a bit. Let's print out the differences between the two z-coordinates:

```python
import bpy

original = bpy.data.objects['Original']
modified = bpy.data.objects['Modified']
for i in range(len(original.data.vertices)):
    if original.data.vertices[i].co != modified.data.vertices[i].co:
        print(original.data.vertices[i].co.z - modified.data.vertices[i].co.z)
```

Output:
```
0.009800001978874207
0.009900003671646118
0.009700000286102295
...
```


Hmm... these numbers look familiar. The ASCII values of `98`, `99`, and `97`, respectively, are `b`, `c`, and `a`. Let's multiply the differences by `10000`, round them, and get the corresponding ASCII characters:

```python
import bpy

original = bpy.data.objects['Original']
modified = bpy.data.objects['Modified']
flag = ""
for i in range(len(original.data.vertices)):
    if original.data.vertices[i].co != modified.data.vertices[i].co:
        diff = (modified.data.vertices[i].co.z - original.data.vertices[i].co.z) * 10000
        flag += chr(round(diff))
print(flag)
```

Output:
```
bcactf{b13nD3R_m0nK3Y_5hifHJf}
```


There's our flag!
