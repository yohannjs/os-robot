import sys
import numpy as np
import matplotlib.pyplot as plt
import scantools as st

# Make sure the user supplies a sample file
if len(sys.argv) < 3:
    print("Please supply both input and output file")
    exit()

# Loads samples from file
# Returns a list of size 360 with one distance per heading angle
# File should have lines on the form:
# <heading><tab><distance><newline>
distances = st.loadSamples(sys.argv[1], 1000)

# Saves samples
st.saveSamples(distances, sys.argv[2]);

print("Samples saved.");
