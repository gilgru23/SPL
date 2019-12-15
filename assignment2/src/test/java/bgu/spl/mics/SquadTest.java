package bgu.spl.mics;

import bgu.spl.mics.application.passiveObjects.Agent;
import bgu.spl.mics.application.passiveObjects.Squad;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import java.util.Arrays;

import java.util.List;

import static org.junit.jupiter.api.Assertions.fail;

public class SquadTest {
    private Squad squad;
    List<String> serials;
    private Agent[] agents;
    @BeforeEach
    public void setUp(){
        squad =Squad.getInstance();
        agents= new Agent[6] ;
        for(int i=0;i<6;i++)
        {
            serials.add(""+i);
            agents[i]=new Agent();
            agents[i].setSerialNumber(serials.get(i));
            agents[i].setName("Moshe"+i);
        }
        squad.load(agents);
    }

    @Test
    public void testReleaseAgents(){
        String[]serial={"1","2","4"};
        List<String> check = Arrays.asList(serial);
        squad.releaseAgents(check);
        assert(agents[1].isAvailable());
        assert(agents[2].isAvailable());
        assert(agents[4].isAvailable());
    }
    public void testGetAgents() {
        String[] serial = {"1", "3", "5"};
        List<String> check = Arrays.asList(serial);
        squad.getAgents(check);
        assert(!agents[1].isAvailable());
        assert(!agents[3].isAvailable());
        assert(!agents[5].isAvailable());
    }

    public void testGetAgentsNames(){
        List<String> check = squad.getAgentsNames(serials);
        for(int i=0;i<agents.length;i++)
        {
            assert(check.contains(agents[i].getName()));
        }
    }
    public void testSendAgents(){
        agents[1].acquire();
        agents[3].acquire();
        agents[4].acquire();
        String[] serial = {"1", "3", "4"};
        List<String> check = Arrays.asList(serial);
        squad.sendAgents(check,80000);
        assert(agents[1].isAvailable());
        assert(agents[3].isAvailable());
        assert(agents[4].isAvailable());
    }



}
