package dataStructures;

import agents.Agent;

import java.util.*;

public class DisjointSetMap
{
    private Map<Integer, Integer> parent = new HashMap<>(); // identifies group agent is in
    private Map<Integer, List<Agent>> values = new HashMap<>(); // agents in group
    private Map<Integer, Double> optimalCost = new HashMap<>(); // optimal path cost of group
    private Map<Integer, Integer> rank = new HashMap<>();    // depth (rank) of each tree

    public void makeSet(List<Agent> agents)
    {
        // create n disjoint sets (one for each item)
        for (Agent a : agents)
        {
            Integer id = ((Agent) a).getId();

            parent.put(id, id);
            rank.put(id, 0);
            values.put(id, new ArrayList<Agent>());
            values.get(id).add(a);
            optimalCost.put(id, a.getPath().getCost());
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
            optimalCost.replace( x, optimalCost.get(x) + optimalCost.get(y) );
            optimalCost.replace( y, 0.0 );
        }
        else if (rank.get(x) < rank.get(y))
        {
            parent.put( x, y );
            values.get( y ).addAll( values.get( x ) );
            values.get( x ).clear();
            optimalCost.replace( y, optimalCost.get(y) + optimalCost.get(x) );
            optimalCost.replace( x, 0.0 );
        }
        else
        {
            parent.put(x, y);
            rank.put(y, rank.get(y) + 1);
            values.get( y ).addAll( values.get( x ) );
            values.get( x ).clear();
            optimalCost.replace( y, optimalCost.get(y) + optimalCost.get(x) );
            optimalCost.replace( x, 0.0 );
        }
    }

    public void printSets(){
        for ( Map.Entry<Integer, List<Agent>> entry : values.entrySet() ){
            System.out.println( "Agent: " + entry.getKey().toString() +
                    " Group: " + entry.getValue());
        }
    }

    public List<Agent> getGroupAgents(Integer groupId)
    {
        return values.get( groupId );
    }

    public double getGroupCost(Integer groupId)
    {
        return optimalCost.get( groupId );
    }

    public List<Integer> getGroupAgentIds(Integer groupId){
        List<Integer> ids = new ArrayList<>();
        for ( Agent agent : getGroupAgents( parent.get(groupId) ) ){
            ids.add( agent.getId() );
        }
        return ids;
    }

}