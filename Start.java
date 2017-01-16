/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package uzivatelskeRozhrani.obsahyOkna;

import javafx.geometry.Insets;
import javafx.scene.Node;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.text.Text;

/**
 *
 * @author jitka
 */
public class Start extends VBox {
    
    public final Button startuj;
     public final Button odhlasit;
    public final Button ukoncit;
    
    public Start(){
        this.setSpacing(40);
        this.setPadding(new Insets(20,30,20,30));
       
        
        startuj = new Button("Start");
        odhlasit = new Button ("Odhlásit");
        ukoncit = new Button ("Zapomenout");
        this.getChildren().addAll(getHorni(), getStred(), getSpodek(), getPodpis());
    }
    
    private Node getHorni(){
        Text a = new Text("     Vítejte ve hře DuelKvíz");
         a.setFont(javafx.scene.text.Font.font(25));
        a.setFill(Color.BLUE);
       
        return a;
    }
    
   private Node getStred(){
        Label text = new Label("V této hře Vám bude postupně předloženo deset otázek \n"
                             + "na které budete odpovídat. Na výběr budete mít vždy \n"
                             + "ze třech možnosí, přižemž pouze jedna je správná. \n"
                             + "Po zodpovězení poslední otázky se dozvíte, zda jste \n"
                             + "soupeře porazili či nikoliv.\n\n"
                             + "Přeji hodně štěstí ve hře. \n\n"
                            + "Nyní jste úspěšně přihlášeni. Pokud chcete zahájit hru,\n"
                             + "stikněte tlačítko \"Start\".") ;
       
        return text;
    }
   
    private Node getSpodek(){
           HBox tlacitka = new HBox();
            this.setPadding(new Insets(50));
           tlacitka.setSpacing(50);
           odhlasit.setMinSize(100, 40);
           ukoncit.setMinSize(100,40);
           startuj.setMinSize(100,40);
           tlacitka.getChildren().addAll(startuj,odhlasit,ukoncit);
           return tlacitka;

    }
    
     private Node getPodpis(){
        Label l = new Label("    Tato hra je vyvíjena jako semestrální práce KIV/UPS. \n\n                        @Jitka Fürbacherová");
        return l;
    }
}
