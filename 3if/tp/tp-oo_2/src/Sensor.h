#ifndef SENSOR_H
#define SENSOR_H

#include "EventLink.h"

/* Forward declarations */
class Event;
template <typename E> class SegmentedTable;

/**
 * Represents a city's sensor, storing links to events which it has generated.
 *
 * The sensor does not store the events themselves, which must be stored
 * elsewhere; it simply maintains a table of links pointing to those events.
 * This provides a way to look up events by sensor ID instead of by day.
 */
class Sensor {
public:
    /**
     * Initializes a new sensor with an ID and no events.
     *
     * @param sensorId the unique ID of the sensor
     * @param segmentSize the size of individual segments
     * @param maxSegments the maximum number of segments to be allocated
     */
    Sensor(
            unsigned int sensorId, unsigned int segmentSize,
            unsigned int maxSegments);

    /**
     * Destructs a sensor and its list of linked events.
     */
    virtual ~Sensor();

    /**
     * Links a new event to the sensor.
     *
     * All linked events are considered as having been generated by this sensor.
     * @param el the new link to an event
     */
    void addEventLink(EventLink el);

    /**
     * Fetches an event by following a link to it.
     *
     * The method requires a table of events sorted by day to look up the event.
     * @param i the index of the event in the day's table
     * @param events an array of days' events to look up the event in
     * @return the linked event
     */
    Event getEvent(unsigned int i, SegmentedTable<Event>* const events[]) const;

    /**
     * Fetches the link to an event by its position in this sensor's link table.
     *
     * @param i the index of the event link in the table
     * @return the link to an event
     */
    EventLink getEventLink(unsigned int i) const;

    /**
     * Returns the sensor's ID.
     *
     * @return the sensor's ID
     */
    unsigned int getId() const;

    /**
     * Counts the total number of event links (and so events) and returns it.
     *
     * @return the number of linked events
     */
    unsigned int getNumEvents() const;

protected:
    /**
     * The ID uniquely identifying the sensor.
     */
    unsigned int id;

    /**
     * A segmented table of all events linked to the sensor.
     */
    SegmentedTable<EventLink>* eventLinks;
};


#endif // SENSOR_H
