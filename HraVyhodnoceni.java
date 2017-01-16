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
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.Text;

/**
 *
 * @author jitka
 */
public class HraVyhodnoceni extends VBox {

    public final Button odhlasit;
    public final Button ukoncit;
    public final Button start;

    public HraVyhodnoceni(int vysledek) {
        this.setSpacing(60);
        this.setPadding(new Insets(60, 40, 70, 40));
        odhlasit = new Button("Odhlásit");
        ukoncit = new Button("Zapomenout");
        start = new Button("Hrát znovu");
        this.getChildren().addAll(getHorni(), getStred(vysledek), getSpodek(), getPodpis());
    }

    private Node getHorni() {
        Text a = new Text("           DuelKvíz");
        a.setFont(javafx.scene.text.Font.font(35));
        a.setFill(Color.BLUE);

        return a;
    }

    public Node getStred(int vysledek) {
        Text text = new Text();
        if (vysledek == 1) {
            text.setText("       Vyhrál jste!");
            text.setFont(Font.font("Verdana", 40));
            text.setFill(Color.GREEN);
        } else if (vysledek == 2) {
            text.setText("Bohužel jste prohrál :( .");
            text.setFont(Font.font("Verdana", 40));
            text.setFill(Color.RED);
        } else if (vysledek == 0) {
            text.setText("      Remíza! ");
            text.setFont(Font.font("Verdana", 50));
            text.setFill(Color.ORANGE);
        }

        return text;
    }

    private Node getSpodek() {
        HBox tlacitka = new HBox();
        tlacitka.setSpacing(50);
        odhlasit.setMinSize(100, 40);
        ukoncit.setMinSize(100, 40);
        start.setMinSize(100, 40);
        tlacitka.getChildren().addAll(odhlasit, start, ukoncit);
        return tlacitka;

    }

    private Node getPodpis() {
        Label l = new Label("    Tato hra je vyvíjena jako semestrální práce KIV/UPS. \n\n                        @Jitka Fürbacherová");
        return l;
    }
}
