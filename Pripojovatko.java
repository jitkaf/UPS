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
import javafx.scene.text.Font;
import javafx.scene.text.Text;

/**
 *
 * @author jitka
 */
public class Pripojovatko extends VBox {
    
    private TextArea ipText;
    private Text info;
    private TextArea portText;
    
    public final Button pripoj;
    public final Button konec;
    public Pripojovatko(int opakovani){
       pripoj = new Button("Připoj");
       konec = new Button("Ukončit");
       this.setSpacing(40);
       this.setPadding(new Insets(30));
       this.getChildren().addAll(getIpCast(), getPortCast(), getTlacitka(), getPopisek(opakovani));
       
      
       
        
    }
    
    private Node getIpCast(){
        HBox ip = new HBox();
        Text t = new Text ("   IP adresa:      ");
     //   t.setFont(Font.font ("Verdana", 30));
        Label popisekIp = new Label(t.getText());
        ipText = new TextArea();
        ipText.setMaxSize(300, 50);
        ip.getChildren().addAll(popisekIp, ipText);
        
        return ip;
    }
    
    private Node getPortCast(){
        HBox port = new HBox();
        Text t = new Text ("   Adresa portu: ");
       // t.setFont(Font.font ("Verdana", 70));
        Label popisekPort = new Label(t.getText());
        portText = new TextArea();
        portText.setMaxWidth(300);
        portText.setMaxHeight(50);
        port.getChildren().addAll(popisekPort, portText);
        
        return port;
    }
    
    private Node getTlacitka(){
        HBox tl = new HBox();
        pripoj.setMinSize(150, 40);
        konec.setMinSize(150, 40);
        tl.setSpacing(50);
        tl.setPadding(new Insets(30));
        tl.getChildren().addAll(pripoj, konec);
        return tl;
                
    }
    
    
    private Node getPopisek(int vysledek){
        if (vysledek == 1 ) {
             info = new Text ("Došlo k neočekávanému nepříjmenému odpojení od serveru. \nPro pokračování je nutné se znovu připojit k serveru \na provést novou registraci hráče. \n \n           Omlouváme se za komplikace.");
             
        }
       else  if (vysledek == 2){
            info = new Text ("               Port musí být číslo od 0 do 65535!");
        }
       else if (vysledek == 3){
           info = new Text ("       Připojeni selhalo, zadejte prosim IP adresu a port lépe.");
       }
        else {
            info = new Text ("");
        }
        info.setFont(Font.font ("Verdana", 20));
        info.setFill(Color.RED);
        Label infoLabel = new Label (info.getText());
        return infoLabel;
    }
    
    
    public String getIpText(){
        return ipText.getText();
    }
    
    public String getPortText(){
        return portText.getText();
    }
    
    public void setInfoLabel(String s){
        info.setText(s);
    }
    
}
