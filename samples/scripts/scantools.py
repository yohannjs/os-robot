# Returns a list of all the samples, the list contains lists where the first
# element is the heading and the second element is the distance
def loadSamplesRaw(filename):
    samples = []
    samplefile = open(filename, "r")
    for line in samplefile:
        sample = line.strip().split("\t")
        samples.append([int(sample[0]), int(sample[1])])
    samplefile.close()
    return samples

# Returns a list containing two lists: one with the headings and one with the 
# distances
def loadSamplesRaw2(filename):
    heading = []
    distance = []
    samples = loadSamplesRaw(filename)
    for sample in samples:
        heading.append(sample[0])
        distance.append(sample[1])
    return [heading, distance]

# Returns the samples as a 360-element list, where each element is the distance
# in the direction of the index. It also restricts distances to a maximum
# distance. Angles that have no corresponding distance will be set to the 
# maximum distance
def loadSamples(filename, maxdistance):
    distances = [0] * 360
    samples = loadSamplesRaw(filename)
    headings = [s[0] for s in samples]
    for sample in samples:
        angle = sample[0]
        distance = sample[1]
        distances[angle] += distance / headings.count(angle)
    for i in range(360):
        if distances[i] == 0 or distances[i] > maxdistance:
            distances[i] = maxdistance
    return distances

# Runs a list of samples through a simple first order filter with specifiable
# a0 and a1.
def filterSamples(samples, a0, a1):
    samplenumber = len(samples)
    filteredsamples = samples.copy() 
    filteredsamples[0] = a0 * samples[0] + a1 * samples[samplenumber - 1]
    for i in range(1, samplenumber):
        filteredsamples[i] = a0 * samples[i] + a1 * samples[i - 1]
    return filteredsamples