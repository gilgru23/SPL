package bgu.spl.mics.application;


import bgu.spl.mics.Event;
import bgu.spl.mics.MessageBroker;
import bgu.spl.mics.MessageBrokerImpl;
import bgu.spl.mics.Subscriber;
import bgu.spl.mics.application.messages.AgentsAvailableEvent;
import bgu.spl.mics.application.passiveObjects.Agent;
import bgu.spl.mics.application.passiveObjects.Inventory;
import bgu.spl.mics.application.passiveObjects.MissionInfo;
import bgu.spl.mics.application.passiveObjects.Squad;
import bgu.spl.mics.application.publishers.Intelligence;
import bgu.spl.mics.application.publishers.TimeService;
import bgu.spl.mics.application.subscribers.M;
import bgu.spl.mics.application.subscribers.Moneypenny;
import bgu.spl.mics.example.messages.ExampleEvent;
import bgu.spl.mics.example.subscribers.ExampleEventHandlerSubscriber;
import com.google.gson.*;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.Reader;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentLinkedQueue;

/** This is the Main class of the application. You should parse the input file,
 * create the different instances of the objects, and run the system.
 * In the end, you should output serialized objects.
 */
public class MI6Runner {
    private static List<Intelligence> intelligenceList;
    private static Squad squad;
    private static Inventory inventory;
    private static M m;
    private static Moneypenny moneyp;
    private static TimeService timeSrv;

    public static void main(String[] args) {
        intelligenceList= new ArrayList<>();
        squad = Squad.getInstance();
        inventory= new Inventory();
        parseInput(args[0]);
    }



    private static void parseInput(String path)
    {
        Gson gson = new Gson();
        FileReader reader = null;
        JsonObject jObject = null;
        try {
            reader = new FileReader(path);
            jObject = gson.fromJson(reader,JsonObject.class);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        getInventory(jObject);
        //getSquad(jObject);
        //TODO: getM , getMoneyPenny
        getintelligenceList(jObject);
        getSquad(jObject);
    }

    private static void getintelligenceList(JsonObject jObject) {
        JsonArray intels = jObject.get("services").getAsJsonObject().
                            get("intelligence").getAsJsonArray();
        int intelName = 0;
        for(JsonElement intelElement: intels)
        {
            intelName++;
            JsonArray missions=intelElement.getAsJsonObject().get("missions").getAsJsonArray();
            List<MissionInfo> missionsList = new ArrayList<>();
            for (JsonElement missionElement:missions)
            {
                JsonObject mission = missionElement.getAsJsonObject();
                MissionInfo newMission = new MissionInfo();
                newMission.setMissionName(mission.get("name").getAsString());
                newMission.setGadget(mission.get("gadget").getAsString());
                newMission.setDuration(mission.get("duration").getAsInt());
                newMission.setTimeExpired(mission.get("timeExpired").getAsInt());
                newMission.setTimeIssued(mission.get("timeIssued").getAsInt());

                JsonArray agents = mission.get("serialAgentsNumbers").getAsJsonArray();
                List<String> agentsNumbers = new ArrayList<>();
                for (JsonElement agentElement:agents)
                {
                    agentsNumbers.add(agentElement.getAsString());
                }
                newMission.setSerialAgentsNumbers(agentsNumbers);
                missionsList.add(newMission);
            }
            intelligenceList.add(new Intelligence(Integer.toString(intelName),missionsList));
        }
    }

    private static void getSquad(JsonObject jObject) {
        JsonArray agents = jObject.get("squad").getAsJsonArray();
        Agent[] agentsArray = new Agent[agents.size()];
        int i=0;
        for (JsonElement a:agents)
        {
            JsonObject o =a.getAsJsonObject();
            agentsArray[i]= new Agent();
            agentsArray[i].setSerialNumber(o.get("serialNumber").getAsString());
            agentsArray[i].setSerialNumber(o.get("name").getAsString());
            agentsArray[i].release();
            i++;
        }
        squad.load(agentsArray);
    }


    private static void getInventory(JsonObject jObject) {
        JsonArray gadgets = jObject.get("inventory").getAsJsonArray();
        String[] gadgetsArray = new String[gadgets.size()];
        int i=0;
        for (JsonElement g:gadgets)
        {
            gadgetsArray[i]=g.getAsString();
            i++;
        }
        inventory.load(gadgetsArray);
        System.out.println(gadgetsArray[0]);
    }
}
