package bgu.spl.mics;

import bgu.spl.mics.example.messages.ExampleBroadcast;
import bgu.spl.mics.example.messages.ExampleEvent;
import bgu.spl.mics.example.subscribers.ExampleBroadcastSubscriber;
import bgu.spl.mics.example.subscribers.ExampleEventHandlerSubscriber;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.fail;

public class MessageBrokerTest {
    private MessageBrokerImpl broker;
    @BeforeEach
    public void setUp(){
        broker = new MessageBrokerImpl();

    }

    /*
    @Test
    public void testSubscribeEvent(){
        Subscriber subscriber=
                new ExampleEventHandlerSubscriber("Moshe",new String[2]);

        broker.subscribeEvent(ExampleEvent.class,subscriber);
    }*/


    @Test
    public void testEventFlow(){

        Subscriber suber=
                new ExampleEventHandlerSubscriber("Yakov",new String[1]);
        broker.register(suber);
        broker.subscribeEvent(ExampleEvent.class,suber);
        Event<String> e=new ExampleEvent("Moshe");
        broker.sendEvent(e);
        Message msg=null;
        try
        {msg=broker.awaitMessage(suber);}
        catch(InterruptedException err)
        {}
        assert(msg==e);
    }

    @Test
    public void testBroadcastFlow(){
        Subscriber suber=
                new ExampleBroadcastSubscriber("Yakov",new String[1]);

        broker.register(suber);
        broker.subscribeBroadcast(ExampleBroadcast.class,suber);
        Message msg=null;
        Broadcast b=new ExampleBroadcast("Moshe");
        broker.sendBroadcast(b);
        try{msg=broker.awaitMessage(suber);}
        catch(InterruptedException e)
        {}
        assert(msg==b);
    }

}
