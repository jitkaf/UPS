/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package uzivatelskeRozhrani.obsahyOkna;

import javafx.scene.control.Button;
import javafx.scene.control.TextArea;
import javafx.scene.layout.VBox;

/**
 *
 * @author jitka
 */
public class Start extends VBox {
    
    public final Button startuj;
    
    public Start(){
        TextArea info = new TextArea(" \n \n             Vítejte ve hře DuelKvíz. \n \n \n V této hře Vám bude postupně předloženo deset otázek na které budete odpovídat. \n  Na výběr budete mít vždy ze třech možnosti a pouze jedna je správná. \n Po zodpovězení poslední otázky se dozvíte, zda jste vyhráli, prohráli či remizovali. Přeji mnoho zdaru. \n Nyní jste úspěšně přihlášeni. Pokud chcete zahájit hru, stikněte tlačítko níže.") ;
       info.setPrefRowCount(10);
       info.setPrefColumnCount(50);
        info.setEditable(false);
        startuj = new Button("Začít hrát");
        this.getChildren().addAll(info,startuj);
    }
    
  
}
