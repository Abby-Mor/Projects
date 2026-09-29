import time
import matplotlib.pyplot as plt
from resizeable_image import ResizeableImage
import numpy as np


filenames = ['2x2.png','3x3.png', '4x4.png','10x10.png', '200x200.png', '300x300.png', '400x400.png', '500x500.png',
                '600x600.png', '700x700.png', '800x800.png', '900x900.png', '1000x1000.png']
sizes = [2,3,4,10, 200, 300, 400, 500, 600, 700, 800, 900, 1000]
dp_times = []
naive_times = []

for filename in filenames:
    image = ResizeableImage(filename)
    start = time.time() 
    seam = image.best_seam(dp=True)
    dp_times.append(time.time() - start)
    print('Finished DP for ', filename)

for filename in filenames:
    size = int(filename.split('x')[0])
    
    if size > 4:   # cutoff for exponential explosion
        break
    
    image = ResizeableImage(filename)
    start = time.time()
    image.best_seam(dp=False)
    naive_times.append(time.time() - start)
    print("Finished naive for", filename)

#make a list of the file names, run through the file names and call best seam on each one, put the time in the for loop
#append the times to a list

plt.scatter(sizes, dp_times, label="Dynamic Programming")
plt.xlabel("Image width (pixels)")
plt.ylabel("Running time (seconds)")
plt.legend()
plt.show()