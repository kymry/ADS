package dataStructures;

import agents.Agent;

import java.util.*;

public class DisjointSetMapNumber
{
    private Map<Integer, Integer> parent = new HashMap<>(); // identifies group agent is in
    private Map<Integer, List<Integer>> values = new HashMap<>(); // agents in group
    private Map<Integer, Integer> rank = new HashMap<>();    // depth (rank) of each tree

    public void makeSet(List<Integer> agents)
    {
        // create n disjoint sets (one for each item)
        for (Integer a : agents)
        {
            parent.put(a, a);
            rank.put(a, 0);
            values.put(a, new ArrayList<Integer>());
            values.get(a).add(a);
        }
    }

    public Integer find(Integer k)
    {
        // if k is not the root
        if (!parent.get(k).equals(k))
            // path compression
            parent.put(k, find(parent.get(k)));

        return parent.get(k);
    }

    public void union(Integer a, Integer b)
    {
        // find roots of each disjoint set
        Integer x = find(a);
        Integer y = find(b);

        // if already in same set, do nothing
        if (x.equals(y))
        {
            return;
        }
        // Perform union by rank
        if (rank.get(x) > rank.get(y))
        {
            parent.put( y, x );
            values.get( x ).addAll( values.get( y ) );
            values.get( y ).clear();

        }
        else if (rank.get(x) < rank.get(y))
        {
            parent.put( x, y );
            values.get( y ).addAll( values.get( x ) );
            values.get( x ).clear();

        }
        else
        {
            parent.put(x, y);
            rank.put(y, rank.get(y) + 1);
            values.get( y ).addAll( values.get( x ) );
            values.get( x ).clear();

        }
    }

    public void printSets(){
        for ( Map.Entry<Integer, List<Integer>> entry : values.entrySet() ){
            System.out.println( "Agent: " + entry.getKey().toString() +
                    " Group: " + entry.getValue());
        }
    }

    public List<Integer> getGroupAgents(Integer groupId)
    {
        return values.get( groupId );
    }


    public List<Integer> getGroupAgentIds(Integer groupId){
        List<Integer> ids = new ArrayList<>();
        for ( Integer agent : getGroupAgents( parent.get(groupId) ) ){
            ids.add( agent );
        }
        return ids;
    }

}
