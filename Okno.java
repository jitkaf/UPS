package uzivatelskeRozhrani;


import javafx.application.Application;

import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.CheckBox;
import javafx.scene.control.Label;
import javafx.scene.control.RadioButton;
import javafx.scene.control.Spinner;
import javafx.scene.control.TextArea;
import javafx.scene.control.Toggle;
import javafx.scene.control.ToggleGroup;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;
import logika.ProstrednikPoslat;




public class Okno extends Application implements Runnable
{
   private static ProstrednikPoslat prostrednikPos;
    static void launch(Class<Okno> aClass, ProstrednikPoslat prostrednikP) {
        prostrednikPos=prostrednikP;
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
        
	private BorderPane okno; //tohle budu predavat
	private TextArea vstup = new TextArea();
	private TextArea vystup = new TextArea();
	private TextArea posunl = new TextArea();
	private TextArea posuns = new TextArea();
	Spinner posun, posun2;
	private TextArea klic;
	private CheckBox auto ;
	private int indexSifry=0;
	
       public Okno(ProstrednikPoslat prostrednikPos){
           this.prostrednikPos=prostrednikPos;
       }


/**
	 * Vykreslí okno aplikce
	 */
	@Override
	public void start(Stage s) throws Exception {
		s.setTitle("Vědomostní kvíz");
		s.setScene(new Scene(sestavDoBorderPane()));
		s.setMinHeight(950);
		s.setMinWidth(900);
		s.setMaxHeight(1000);
		s.setMaxWidth(900);
		s.show();
	}
	

	/*
	 * Sestaví připravené komponenty do jednoho okna
	 */
	private Parent sestavDoBorderPane() {
		
		okno = new BorderPane();
		//přidá připravené komponenty na určenou pozici
		okno.setCenter(getNeutralniPane());
		okno.setRight(getPravyPane());
		okno.setLeft(getRadioButtony());
		okno.setBottom(getSpodniPanel());
		okno.setTop(getHorniPane());
		
		return okno;
	}
	
	
	/*
	 * Připraví komponentu TextArea
	 */
	private Node getTextArea() {
		
		TextArea text = new TextArea("");

		//nastaví preferované hodnoty počtu řádků a sloupců
		text.setPrefColumnCount(10);
		text.setPrefRowCount(25);
		
		return text;
	}
	
	/**
	 * Vytvori komponentu PravyPane, ve které jsou všechna tlačítka. Stará se také o jejich obsluhu.
	 * @return
	 */
	private Node getPravyPane(){
		VBox buttony = new VBox();
		buttony.setSpacing(30);
		buttony.setPadding(new Insets(30));
		
		//tvorba tlacitek
		Button sifruj = new Button("Šifruj");
		Button desifruj = new Button("Dešifruj");
		Button frek = new Button("Frekvenční analýza");
                Button poslat = new Button("Odeslat odpověd");
		//prida akci k tlacitku sifruj
		sifruj.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
            	//vyber sifrovaci metody podle zvoleneho radiobuttonu
            	switch (indexSifry) {
    			
    			/*case 1: Atbas a = new Atbas();
    					vystup.setText(a.vymen(vstup.getText().toUpperCase()));
    					break;*/
    			/*case 2:	Cezar c = new Cezar(vstup.getText().toUpperCase());
    					int posunout = (int) posun.getValue();
    					vystup.setText(c.sifruj(vstup.getText().toUpperCase(), posunout));
    					break;/*
    			case 3: Albert al = new Albert(vstup.getText().toUpperCase());
    					vystup.setText(al.sifruj((int)posun.getValue(),(int) posun2.getValue(), true));
    					break;
    			case 4: Viegener v = new Viegener();
    					vystup.setText(v.desifruj(vstup.getText().toUpperCase(), klic.getText().toUpperCase(), true));
    					break;*/
    			
    		}
		    	
            }
        });
		//prida akci k tlacitku desifruj
		desifruj.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
		    //		FrekvencniAnalyza f = new FrekvencniAnalyza();
	    			///f.setAktualni(vstup.getText().toUpperCase());
	            	//vyber sifrovaci metody podle zvoleneho radiobuttonu

		    		switch (indexSifry) {
		    			/*case 1: Atbas a = new Atbas();
		    					vystup.setText(a.vymen(vstup.getText().toUpperCase()));
		    					break;*/
		    			/*case 2:	Cezar c = new Cezar(vstup.getText().toUpperCase(), f.getAktualni());
		    					int posunout = auto.isSelected() ? c.najdiPosun() : (int) posun.getValue();
		    					vystup.setText(c.desifruj(vstup.getText().toUpperCase(), posunout));
		    					if (auto.isSelected()){
		    						posunl.setText(""+c.getposs());
		    					}
		    					break;/*
		    			case 3: Albert al = new Albert(vstup.getText().toUpperCase());
		    					if (auto.isSelected()){
		    						vystup.setText(al.desifrujAuto());
		    						posunl.setText("" + al.getPosunL());
		    						posuns.setText("" + al.getPosunP());
		    					}
		    					else{
		    						vystup.setText(al.sifruj((int)posun.getValue(),(int) posun2.getValue(), false));
		    					}
		    					break;
		    			case 4: Viegener v = new Viegener();
		    					vystup.setText(v.desifruj(vstup.getText().toUpperCase(), klic.getText().toUpperCase(), false));
		    					break;
		    			case 5: Alex ale = new Alex();
		    					vystup.setText(ale.desifruj(vstup.getText().toUpperCase()));
		    					break;*/
		    		}
            }
        });
		//prida akci k tlacitku frek
		frek.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
		    	/*FrekvencniAnalyza frekvencniAnalyza = new FrekvencniAnalyza();
		    	frekvencniAnalyza.setAktualni(vstup.getText().toUpperCase());
		    	/*Graf graf = new Graf("Frekvenční analýza - aktuální", frekvencniAnalyza.getAktualni());
		    	graf.pack();
		        RefineryUtilities.centerFrameOnScreen(graf);
		        graf.setVisible(true);
		        Graf grafCestina = new Graf("Frekvenční analýza - čeština", frekvencniAnalyza.getCestina());
		    	grafCestina.pack();
		        RefineryUtilities.centerFrameOnScreen(graf);
		        grafCestina.setVisible(true);*/
		    	
            }
        });
		
		buttony.getChildren().addAll(sifruj, desifruj, frek);
		return buttony;
	}
	
	/**	
	/*
	 * Vytvoří panel s radiobuttons a levé straně okna
	 */
	private Node getRadioButtony() {
		
		VBox radioButtony = new VBox();

		//skupina, aby sel oznacit jen jeden RB ze skupiny
		ToggleGroup toggleGroupTG = new ToggleGroup();
		
		//vytvoreni noveho RB s moznosti
		RadioButton atbas = new RadioButton("ATBAŠ");
		RadioButton cezar = new RadioButton("Cézarova šifra");
		RadioButton albert = new RadioButton("Albertiho šifra");
		RadioButton viegener = new RadioButton("Viegenerova šifra");
		RadioButton alex = new RadioButton("Alexova šifra");
			
			
		//prida do skupiny kvuli klikani
		atbas.setToggleGroup(toggleGroupTG);
		cezar.setToggleGroup(toggleGroupTG);
		albert.setToggleGroup(toggleGroupTG);
		viegener.setToggleGroup(toggleGroupTG);
		alex.setToggleGroup(toggleGroupTG);
			
			
		radioButtony.getChildren().add(atbas);
		radioButtony.getChildren().add(cezar);
		radioButtony.getChildren().add(albert);
		radioButtony.getChildren().add(viegener);
		radioButtony.getChildren().add(alex);
		
		//mezery mezi RB a vycentrovani na vysku
		radioButtony.setSpacing(20);		
		radioButtony.setPadding(new Insets(20));

		//prida akce k zaskrnuti
		toggleGroupTG.selectedToggleProperty().addListener(new ChangeListener<Toggle>() {
	        @Override
	        public void changed(ObservableValue<? extends Toggle> ov, Toggle t, Toggle t1) {

	            RadioButton chk = (RadioButton)t1.getToggleGroup().getSelectedToggle(); // Cast object to radio button

	            //zde budu překreslovat panel
	            okno.setCenter(new Button(chk.getText()));

	            if (chk.getText().equals("ATBAŠ")){
	            	okno.setCenter(getNeutralniPane());
	            	indexSifry=1;
	            }
	            else if (chk.getText().equals("Cézarova šifra")){
	            	okno.setCenter(getCezarPane());
	            	indexSifry=2;
	            }
	            else if (chk.getText().equals("Albertiho šifra")){
	            	okno.setCenter(getAlbertPane());
	            	indexSifry=3;
	            }
	            else if (chk.getText().equals("Viegenerova šifra")){
	            	okno.setCenter(getViegenerPane());
	            	indexSifry=4;
	            }
	            else{
	            	okno.setCenter(getNeutralniPane());
		           	indexSifry=5;
	            }
	        }
	    });
		
		return radioButtony;
	}
	
	/*
	 * Vytvoří spodní panel
	 */
	private Node getSpodniPanel() {
		BorderPane spodni = new BorderPane();
		spodni.setTop(new Label ("Výstup programu:"));
		spodni.setCenter(vystup);
		return spodni;
	}

	
	/**
	 * Vytvoří horní panel 
	 * @return
	 */
	private Node getHorniPane(){
		BorderPane horni = new BorderPane();
		vstup.setPrefSize(100, 900);
		vstup.setMaxSize(800,150);
		horni.setTop(new Label("Zadejte prosím vstupní řetězec:"));
		horni.setCenter(vstup);
		
		return horni;
	}
	
	/**
	 * Vytvoří panelm ktery používam pri volbe cezarovi sifry
	 * @return
	 */
	private Node getCezarPane(){
		VBox stred = new VBox();
		stred.setSpacing(10);
		stred.setPadding(new Insets(10));
		//popisky
		Label label1 = new Label("Zvolte prosím parametry šifrování \n či dešifrování:");
		Label label2 = new Label("Zadejte prosím posun: ");
		 stred.setAlignment(Pos.CENTER);
		//vytvori spinner pro zadani posunu
		posun = new Spinner(0, 40, 1);
		posun.setEditable(true);
		posun.setMaxWidth(50);
	

		
		//vytvori checkbox
		auto = new CheckBox();
		auto.setText("Zkusit prolomit automaticky.");
		auto.setSelected(false);
		posunl.setMaxSize(20, 20);
		
		stred.getChildren().addAll(label1, label2, posun, auto, new Label ("Vypočtený posun:"), posunl);
		
		return stred;
	}
	
	/**
	 * Vytvori panel, ktery pouzívam pri volbě Albertovo sifry.
	 * @return
	 */
	private Node getAlbertPane(){
		VBox stred = new VBox();
		stred.setSpacing(1);
		stred.setPadding(new Insets(1));
		//popisky
		Label label1 = new Label("Zvolte prosím parametry šifrování \n či dešifrování:");
		Label label2 = new Label("Zadejte prosím posun lichých písmen.");
		Label label3 = new Label("Zadejte prosím posun sudých písmen.");
		stred.setAlignment(Pos.CENTER);
		//spinnnery
		posun = new Spinner(0, 40, 1);
		posun.setEditable(true);
		posun.setMaxWidth(100);
		posun2 = new Spinner(0, 40, 1);
		posun2.setEditable(true);
		posun2.setMaxWidth(100);
		auto = new CheckBox();
		auto.setText("Zkusit prolomit automaticky.");
		auto.setSelected(false);
		Label ll= new  Label("Vypočtený posun lichých znaků:");
		posunl.setMaxSize(20, 20);
		posuns.setMaxSize(20, 20);
		Label ls = new Label("Vypočtený posun sudýých znaků:");
		stred.getChildren().addAll(label1, label2, posun, label3, posun2, auto, ll, posunl, ls, posuns);
		
		return stred;
	}
	
	/**
	 * Vytvori panel, ktery pouzívam pri volbe Viegenerovy sifry.
	 * @return
	 */
	private Node getViegenerPane(){
		VBox stred = new VBox();
		stred.setSpacing(20);
		stred.setPadding(new Insets(20));
		stred.setAlignment(Pos.CENTER);
		//popisky
		Label label1 = new Label("Zvolte prosím parametry šifrování \n či dešifrování:");
		Label label2 = new Label("Zadejte prosím klíčové slovo:");
		//textove pole pro zadani klice
		klic = new TextArea();
		
		stred.getChildren().addAll(label1, label2, klic);
		
		return stred;
	}
	
	/**
	 * Vytvori panel, ktery pouzívam pri volbe jine sifry a pri spusteni aplikace.
	 * @return
	 */
	private Node getNeutralniPane(){
	    VBox stred = new VBox();
	    ///Image im = new Image("pokenom.gif");
	   // ImageView m= new ImageView(im);
	    
	    
	    stred.setAlignment(Pos.CENTER);
	  
	   // stred.getChildren().addAll(m);
	    stred.getChildren().addAll(new Label ("Vyčkejte prosím než hra začne."), new Label ("Čeká se na připojení protihráče."));
	    
		return stred;
	}

    @Override
    public void run() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
}
