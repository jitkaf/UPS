/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package uzivatelskeRozhrani;

import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.control.Button;
import javafx.scene.control.TextArea;
import javafx.scene.layout.VBox;

/**
 *
 * @author jitka
 */
public class Prihlasovatko extends VBox {

    private TextArea jmeno = new TextArea();
    private TextArea heslo = new TextArea();
    private TextArea vysledek = new TextArea();

    public final Button prihlasit;

    public Prihlasovatko() {
        this.setSpacing(30);
        this.setPadding(new Insets(30));

        //nastaví preferované hodnoty počtu řádků a sloupců
        jmeno.setPrefColumnCount(10);
        jmeno.setPrefRowCount(25);
        heslo.setPrefColumnCount(10);
        heslo.setPrefRowCount(25);
        vysledek.setPrefColumnCount(10);
        vysledek.setPrefRowCount(25);
        prihlasit = new Button("Přihlásit");

        this.getChildren().addAll(jmeno, heslo, prihlasit, vysledek);
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
