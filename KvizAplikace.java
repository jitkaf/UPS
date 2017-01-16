
import javafx.application.Application;

import javafx.stage.Stage;

import data.Prostrednik;
import uzivatelskeRozhrani.IPohled;
import uzivatelskeRozhrani.KvizScena;

//import uzivatelskeRozhrani.Okno;
/**
 * Hlavní třída aplikace, vytvoří GUI.
 *
 * @author Jitka Furbacherová
 *
 */
public class KvizAplikace extends Application {

    //ups
    Prostrednik prostrednikPos;

    @Override
    public void start(Stage s) throws Exception {

        prostrednikPos = new Prostrednik();
        prostrednikPos.setData("lalala jsem dato");
        
        KvizScena kvizScena = new KvizScena(prostrednikPos);
        prostrednikPos.setPohled(kvizScena);
        kvizScena.prepniSe(IPohled.PRIPOJENI);

        s.setTitle("Vědomostní kvíz");
        s.setScene(kvizScena);
        s.setMinHeight(500);
        s.setMinWidth(500);
        s.setMaxHeight(600);
        s.setMaxWidth(550);
        s.setY(100);
        s.show();

    }

    /**
     * Main aplikce
     *
     * @param args
     */
    public static void main(String[] args) {
        launch(args);
    }

}
