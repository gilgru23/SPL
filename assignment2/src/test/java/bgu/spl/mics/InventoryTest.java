package bgu.spl.mics;

import bgu.spl.mics.application.passiveObjects.Inventory;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.List;

import static org.junit.jupiter.api.Assertions.fail;

public class InventoryTest {
    Inventory invent;
    String[] example = {"ThunderBall", "SmokeGrande", "RecordingPen", "HiddenCamera", "Shocker"};

    @BeforeEach
    public void setUp() {
        invent = new Inventory();
        invent.load(example);
    }

    @Test
    /*
    public void testLoad() {
        //load method test

        invent.load(example);
        List<String> output = invent.getGadgets();
        for (int j = 0; j < output.size(); j++) {
            try {
                assert (output.get(j).equals(example[j]));
            } catch (Exception e) {
                assert (false);
            }
        }
    }

 */
        public void testGetItem ()
        {
            String gadget1 = "ThunderBall";
            String gadget2 = "Nunchaka";
            String gadget3 = "RecordingPen";
            assert (true == invent.getItem(gadget1));
            assert (false == invent.getItem(gadget2));
            assert (true == invent.getItem(gadget3));

        }
    }

