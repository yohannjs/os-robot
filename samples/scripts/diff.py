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
#diff = st.filterSamples(diff, 1, 0.99, 0.9)

# Run the low pass filtered samples through a high pass filter
filtered = st.filterSamples(diff, 1, -0.99)

# We only care about the absolute size of the high pass filtered samples
# so we take the absolute value of each sample
filtered = [abs(d) for d in filtered]

# Make a list containing all 360 headings in radians, needed for polar plot
heading = np.arange(0, np.pi * 2, np.pi / 180)

# Plot the original signal, the low pass filtered signal and the low pass +
# high pass filtered signal
p1 = plt.subplot(221, projection="polar")
p1.plot(heading, distances1)
p2 = plt.subplot(222, projection="polar")
p2.plot(heading, distances2)
p3 = plt.subplot(223, projection="polar")
p3.plot(heading, diff)
p4 = plt.subplot(224, projection="polar")
p4.plot(heading, filtered)
plt.show()

