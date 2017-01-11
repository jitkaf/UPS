/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package uzivatelskeRozhrani.obsahyOkna;

import java.awt.Font;
import javafx.geometry.Insets;
import javafx.scene.Node;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.text.Text;

/**
 *
 * @author jitka
 */
public class HraCekani extends VBox{
    
     

    public final Button odhlasit;
    public final Button ukoncit;

    public HraCekani(){
        this.setSpacing(25);
        this.setPadding(new Insets(30,40,20,40));
        
        odhlasit = new Button ("Odhlásit");
        ukoncit = new Button ("Ukončit");
        this.getChildren().addAll(getHorni(), getStred(), getSpodek(), getPodpis());
    }


    private Node getHorni(){
        Text a = new Text("             DuelKvíz");
        a.setFont(javafx.scene.text.Font.font(30));
        a.setFill(Color.BLUE);
       
        return a;
    }

    private Node getStred(){
        Label text = new Label("    Hrajete hru DuelKvíz, která Vám přináší velké potěšení. \n \n    Nyní je potřeba chvililinkuku počkat na odevzvu serveru \n    nebo přihlášení soupeře. \n \n"
                + "    V tomto čase se mužete zamyslet nad svým životem.");
        
        return text;
    }
    
    private Node getSpodek(){
           HBox tlacitka = new HBox();
           tlacitka.setPadding(new Insets(50));
           tlacitka.setSpacing(80);
           odhlasit.setMinSize(100, 40);
           ukoncit.setMinSize(100,40);
           tlacitka.getChildren().addAll(odhlasit,ukoncit);
           return tlacitka;

    }
    
    private Node getPodpis(){
        Label l = new Label("    Tato hra je vyvíjena jako semestrální práce KIV/UPS. \n\n                        @Jitka Fürbacherová");
        return l;
    }
}