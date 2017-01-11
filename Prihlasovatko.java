/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package uzivatelskeRozhrani.obsahyOkna;

import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Node;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;

/**
 *
 * @author jitka
 */
public class Prihlasovatko extends VBox {

    private TextArea jmeno = new TextArea();
    private TextArea heslo = new TextArea();
    private TextArea vysledek = new TextArea();
    private int opakovani;
    
    public final Button prihlasit;
    public final Button registrovat;
    public final Button konec;
    public Prihlasovatko(int opakovani) {
        this.opakovani= opakovani;
        this.setSpacing(20);
        this.setPadding(new Insets(10));
        
        
        vysledek.setPrefColumnCount(10);
        vysledek.setPrefRowCount(25);
        //nastaví preferované hodnoty počtu řádků a sloupců
        
        if(opakovani ==1 ){
            vysledek.setText("Zadali jste nesprávné přihlašovací údaje. \nJméno smí obsahovat pouze alfanumerické znaky a nemsí být prázdné."
                    + "\nPokud zadáte více než 20 znaků, budou nadbytečné znaky ignorovány.");
        }
        else if(opakovani==2){
            vysledek.setText("Zadali jste nesprávné přihlašovací údaje. \nHeslo smí obsahovat pouze alfanumerické znaky a nemsí být prázdné."
                    + "\nPokud zadáte více než 20 znaků, budou nadbytečné znaky ignorovány.");
        }
        else if(opakovani == 3){
            vysledek.setText("Toto jméno je již obsazeno. Zadejte jiné jméno. \n"
                    + "Pokud zadáte více než 20 znaků, budou nadbytečné znaky ignorovány.");
        }
        else{
            vysledek.setText("Pokud zadáte více než 20 znaků, budou nadbytečné znaky ignorovány.");
        }
        vysledek.setEditable(false);
        prihlasit = new Button("Přihlásit");
        registrovat = new Button("Registrovat");
        konec = new Button(" Konec  ");
       
        this.getChildren().addAll(getJmenoCast(), getHesloCast(), getTlacitka(), vysledek);
    }

    public Node getJmenoCast(){
        HBox box = new HBox();
        Label popisek = new Label("Zadejte jmeno(max 20 znaků): ");
        jmeno.setPrefColumnCount(10);
        jmeno.setPrefRowCount(25);
        jmeno.setMinSize(150, 30);
        jmeno.setMaxSize(200,40);
        box.setSpacing(50);
        box.setPadding(new Insets(20));
        box.getChildren().addAll(popisek, jmeno);
        return box;
        
    }
    
     private Node getHesloCast(){
        HBox box = new HBox();
        Label popisek = new Label("Zadejte heslo(max 20 znaků): ");
        heslo.setPrefColumnCount(10);
        heslo.setPrefRowCount(25);
        heslo.setMinSize(150, 30);
        heslo.setMaxSize(200, 40);
        box.setSpacing(50);
        box.setPadding(new Insets(20));
        box.getChildren().addAll(popisek, heslo);
        return box;
        
    }
     
     private Node getTlacitka(){
        HBox box = new HBox();
        box.setSpacing(50);
        box.setPadding(new Insets(30));
        prihlasit.setMinSize(100, 40);
        registrovat.setMinSize(100, 40);
        konec.setMinSize(100, 40);
        box.getChildren().addAll(prihlasit, registrovat, konec);
        return box;
         
     }
     
    public String getJmeno() {
        return this.jmeno.getText();
    }
    
    public String getHeslo(){
        return this.heslo.getText();
    }
    
    public void setVysledek(String vysledek){
        this.vysledek.setText(vysledek);
    }
}
