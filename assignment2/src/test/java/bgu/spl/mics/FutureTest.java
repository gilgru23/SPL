package bgu.spl.mics;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.concurrent.ExecutionException;

import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;

import static org.junit.jupiter.api.Assertions.*;

public class FutureTest {
    private Future<String> f;
    @BeforeEach
    public void setUp() {

    f= new Future<>();
    f.resolve("AbraKadabra");

    }

    @Test
    public void testGet(){

        String result=f.get();
        assert(f.isDone());
        assertEquals(result,"AbraKadabra");
    }
    @Test
    public void testGetTime(){

        String result=f.get(4,TimeUnit.SECONDS);
        assertEquals(f.isDone(),result!=null);
        assertEquals(result,"AbraKadabra");

    }
    @Test
    public void testisDone(){
        Future<Integer> fu = new Future<>();
        Integer result=fu.get(4,TimeUnit.SECONDS);
        assert(!fu.isDone());
        fu.resolve(-3);
        assert(fu.isDone());
    }

}
