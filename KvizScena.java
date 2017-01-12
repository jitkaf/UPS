package uzivatelskeRozhrani;

import javafx.application.Platform;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.BorderPane;
import logika.ProstrednikPoslat;

/**
 *
 * @author jitka
 */
public class KvizScena extends Scene implements IPohled {

    private final StavitelObsahuOkna stavitel;
    private final BorderPane layout;
    private final ProstrednikPoslat prostrednik;

    public KvizScena(ProstrednikPoslat prostrednik) {
        super(new BorderPane(new Button("Karel karluje")));
        this.layout = (BorderPane) this.getRoot();
        this.layout.prefWidthProperty().bind(this.widthProperty());
        this.layout.prefHeightProperty().bind(this.heightProperty());
        //this.layout.setBackground(new Background(new BackgroundFill(Color.PURPLE, CornerRadii.EMPTY, Insets.EMPTY)));
        this.stavitel = new StavitelObsahuOkna(prostrednik);
        this.prostrednik = prostrednik;

    }

    private void setObsah(Parent obsah) {
        this.layout.setCenter(obsah);
    }

    @Override
    public void prepniSe(int idPohled) {
        Platform.runLater(() -> {
            System.out.println("Jsem v prepni se idpohled je: " + idPohled);
            switch (idPohled) {
                
                case IPohled.PRIPOJENI:
                    this.setObsah(stavitel.getPripojovatko(0));
                    break;
                case IPohled.PRIPOJENI_ZNOVU:
                    this.setObsah(stavitel.getPripojovatko(1));
                    break;  
                case IPohled.PRIPOJENI_CHYBA_PORTU:
                    this.setObsah(stavitel.getPripojovatko(2));
                    break;
                case IPohled.PRIPOJENI_CHYBA:
                    this.setObsah(stavitel.getPripojovatko(3));
                    break;
                case IPohled.PRIHLASENI:
                    this.setObsah(stavitel.getPrihlasovatko(0));
                    break;
                case IPohled.PRIHLASENI_DUPLICITA:
                    this.setObsah(stavitel.getPrihlasovatko(3));
                    break;
                case IPohled.PRIHLASENI_HESLO:
                    this.setObsah(stavitel.getPrihlasovatko(2));
                    break;    
                case IPohled.PRIHLASENI_JMENO:
                    this.setObsah(stavitel.getPrihlasovatko(1));
                    break;
                case IPohled.START:
                    this.setObsah(stavitel.getStart());
                    break;
                case IPohled.HRA_CEKANI:
                    this.setObsah(stavitel.getHraCekani());
                    break;
                case IPohled.HRA_OTAZKA:
                    this.setObsah(stavitel.getHraOtazka());
                    break;
                case IPohled.HRA_VYHODNOCENI:
                    System.out.println("jdu do vyhodnoceni");
                    this.setObsah(stavitel.getHraVyhodnoceni());
                    break;
                    
                //  case IPohled.KONEC_HRY: this.layout.setCenter(...); break;
                default:
                    System.err.println("Nezname id pohledu: " + idPohled);
                    break;
            }
        });
    }
}