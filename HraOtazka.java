/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package uzivatelskeRozhrani.obsahyOkna;

import javafx.geometry.Insets;
import javafx.scene.Node;
import javafx.scene.control.Button;
import javafx.scene.control.RadioButton;
import javafx.scene.control.TextArea;
import javafx.scene.control.ToggleGroup;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.text.Text;

/**
 *
 * @author jitka
 */
public class HraOtazka extends BorderPane {
    
    private TextArea textOtazky;
    private Text textA;
    private RadioButton a;
    private Text textB;
    private RadioButton b;
    private Text textC;
    private RadioButton c;
    
    public final Button odpovedet;
    public final Button odhlasit;
    public final Button ukoncit;
    public ToggleGroup toggleGroupTG;
    
    public HraOtazka(String otazka, String acko, String becko, String cecko){
        textA = new Text (acko);
        textB = new Text(becko);
        textC = new Text(cecko);
        textOtazky = new TextArea (otazka);
        textOtazky.setEditable(false);
        this.setTop(textOtazky);
        this.setCenter(getProstredek());
        
        odpovedet = new Button ("Odpovědět");
        odpovedet.setPrefSize(100, 30);
        odhlasit = new Button ("Odhlasit");
        ukoncit = new Button ("Ukoncit");
        
        this.setBottom(getSpodek());
        
    }
    
    
    public Node getProstredek(){
        VBox radioButtony = new VBox();
        //skupina, aby sel oznacit jen jeden RB ze skupiny
        toggleGroupTG = new ToggleGroup();
        
        RadioButton a = new RadioButton("A: " +textA.getText());
        RadioButton b = new RadioButton("B: " +textB.getText());
        RadioButton c = new RadioButton("C: " + textC.getText());
        
        a.setToggleGroup(toggleGroupTG);
        b.setToggleGroup(toggleGroupTG);
        c.setToggleGroup(toggleGroupTG);
        
        radioButtony.getChildren().addAll(a,b,c);
        
        radioButtony.setSpacing(20);
        radioButtony.setPadding(new Insets(20));
        
        return radioButtony;
        
    }
    
    
    private Node getSpodek(){
        HBox tlacitka = new HBox();
        tlacitka.setSpacing(50);
        tlacitka.getChildren().addAll(odhlasit,odpovedet,ukoncit);
        return tlacitka;
        
    }
}
