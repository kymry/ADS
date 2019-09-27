package dataStructures;

import java.util.Comparator;
import java.util.TreeSet;

/**
 * Implements a priority queue based on three different comparators. Add, remove, retrieve access is O(log n).
 * Iterates over the heuristic in a round robin fashion
 * @param <E> Class to be compared
 */
public class ThreePriorityQueue<E> {

    private TreeSet<E> q1;
    private TreeSet<E> q2;
    private TreeSet<E> q3;
    private int heuristic = 0;

    public ThreePriorityQueue( Comparator<E> c1, Comparator<E> c2, Comparator<E> c3) {
        q1 = new TreeSet<E>(c1);
        q2 = new TreeSet<E>(c2);
        q3 = new TreeSet<E>(c3);
    }

    public void add (E e) {
        q1.add(e);
        q2.add(e);
        q3.add(e);
    }

    private E pollx (TreeSet<E> a, TreeSet<E> b, TreeSet<E> c) {
        E top = a.first();
        a.remove(top);
        b.remove(top);
        c.remove(top);
        return top;
    }

    public E poll() {
        heuristic = (heuristic == 2) ? 0 : heuristic++;

        switch (heuristic) {
            case (0):
                return pollx( q1, q2, q3 );
            case (1):
                return pollx(q2, q1, q3);
            default:
                return pollx(q3, q1, q2);
        }
    }

    public boolean isEmpty(){
        return q1.size() == 0;
    }
}
