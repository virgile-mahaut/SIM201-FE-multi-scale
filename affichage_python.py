from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import matplotlib.tri as tri
import numpy as np

with open("output.txt") as f:
    content = f.read()

content = content.split("\n")
nb_sommets = int(content[1])
x = np.zeros(nb_sommets)
y = np.zeros(nb_sommets)
z = np.zeros(nb_sommets)
for i in range(2, 2+nb_sommets):
    line = content[i]
    vals = line.split(' ')
    x[i-2]=vals[1]
    y[i-2]=vals[2]
    z[i-2]=vals[3]

nb_triangles = int(content[3+nb_sommets])
triangles = []
for i in range(4+nb_sommets, 4+nb_sommets+nb_triangles):
    line = content[i]
    vals = line.split(' ')
    triangles.append([int(vals[1])-1, int(vals[2])-1, int(vals[3])-1]) 
triangles = np.array(triangles)
# Creating figure 
fig = plt.figure(figsize =(16, 9))   
ax = plt.axes(projection ='3d')   
  
# Creating color map 
my_cmap = plt.get_cmap('hot') 
    
# Creating plot 
trisurf = ax.plot_trisurf(x, y, z, triangles=triangles,
                         cmap = my_cmap, 
                         linewidth = 0.2,  
                         antialiased = True, 
                         edgecolor = 'grey')   
fig.colorbar(trisurf, ax = ax, shrink = 0.5, aspect = 5)   
  
# Adding labels 
ax.set_xlabel('X-axis', fontweight ='bold')  
ax.set_ylabel('Y-axis', fontweight ='bold')  
ax.set_zlabel('Z-axis', fontweight ='bold') 
      
# show plot 
plt.show()
