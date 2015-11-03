template <typename E>
SegmentedTable<E>::SegmentedTable(
        unsigned int segmentSize, unsigned int maxSegments) :
        numSegments(0), numSegmentEntries(0), segmentSize(segmentSize) {
    segments = new E*[maxSegments];
}

template <typename E>
SegmentedTable<E>::~SegmentedTable() {
    for (int i = 0; i < numSegments; i++)
        delete[] segments[i];
    delete[] segments;
}

template<typename E>
unsigned int SegmentedTable<E>::append(E element) {
    if (numSegmentEntries >= segmentSize || numSegments == 0)
        appendSegment();
    segments[numSegments - 1][numSegmentEntries] = element;
    numSegmentEntries++;
    return numSegmentEntries - 1;
}

template <typename E>
const E SegmentedTable<E>::get(unsigned int index) const {
    unsigned short segmentIndex = (unsigned short) (index/segmentSize);
    return segments[segmentIndex][index % segmentSize];
}

template <typename E>
void SegmentedTable<E>::appendSegment() {
    segments[numSegments] = new E[segmentSize];
    numSegments++;
    numSegmentEntries = 0;
}

template<typename E>
const unsigned int SegmentedTable<E>::length() const {
    unsigned int length = 0;
    if (numSegments > 0) {
        length += (numSegments - 1)*segmentSize;
        length += numSegmentEntries;
    }
    return length;
}