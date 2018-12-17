import sys
import numpy as np
import matplotlib.pyplot as plt
import scantools as st

# Make sure the user supplies a sample file
if len(sys.argv) < 3:
    print("Please supply two sample files")
    exit()

# Loads samples from file
# Returns a list of size 360 with one distance per heading angle
# File should have lines on the form:
# <heading><tab><distance><newline>
distances1 = st.loadSamples(sys.argv[1], 1000)
distances2 = st.loadSamples(sys.argv[2], 1000)

# Make a new sample list containing the difference between the two sample files
# given to the script
diff = distances1.copy()
for i in range(360):
    diff[i] = distances1[i] - distances2[i];

# Run the samples through a low pass filter with a0=1, a1=0.95
#lp_distances = st.filterSamples(distances, 1, 0.95)

# Run the low pass filtered samples through a high pass filter
#hp_distances = st.filterSamples(lp_distances, 1, -0.9)

# We only care about the absolute size of the high pass filtered samples
# so we take the absolute value of each sample
#hp_distances = [abs(d) for d in hp_distances]

# Make a list containing all 360 headings in radians, needed for polar plot
heading = np.arange(0, np.pi * 2, np.pi / 180)

# Plot the original signal, the low pass filtered signal and the low pass +
# high pass filtered signal
p1 = plt.subplot(131, projection="polar")
p1.plot(heading, distances1)
p2 = plt.subplot(132, projection="polar")
p2.plot(heading, distances2)
p3 = plt.subplot(133, projection="polar")
p3.plot(heading, diff)
plt.show()

