/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package uzivatelskeRozhrani.obsahyOkna;

import java.awt.Font;
import javafx.scene.Node;
import javafx.scene.control.Button;
import javafx.scene.control.TextArea;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.text.Text;

/**
 *
 * @author jitka
 */
public class HraCekani extends BorderPane{
    
     

    public final Button odhlasit;
    public final Button ukoncit;

    public HraCekani(){
        this.setTop(getHorni());
        this.setCenter(getStred());
        odhlasit = new Button ("Odhlasit");
        ukoncit = new Button ("Ukoncit");
        this.setBottom(getSpodek());
    }


    private Node getHorni(){
        Text a = new Text("                       DuelKvíz");
        a.setFont(javafx.scene.text.Font.font(25));
        TextArea text = new TextArea(a.getText());
        return text;
    }

    private Node getStred(){
        TextArea text = new TextArea("Hrajete hru DuelKvíz, která Vám přináší velké potěšení. \n  Nyní je potřeba chvililinku počkat na odevzdvu serveru či přihlášení soupeře. \n "
                + " V tomto čase se mužete zamyslet nad svým životem a přispět na charitu.");
        
        return text;
    }
    
    private Node getSpodek(){
           HBox tlacitka = new HBox();
           tlacitka.setSpacing(50);
           tlacitka.getChildren().addAll(odhlasit,ukoncit);
           return tlacitka;

    }
}