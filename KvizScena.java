package uzivatelskeRozhrani;

import javafx.application.Platform;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.BorderPane;
import data.Prostrednik;

/**
 *
 * @author jitka
 */
public class KvizScena extends Scene implements IPohled {

    private final StavitelObsahuOkna stavitel;
    private final BorderPane layout;
    private final Prostrednik prostrednik;

    public KvizScena(Prostrednik prostrednik) {
        super(new BorderPane(new Button("Karel karluje")));
        this.layout = (BorderPane) this.getRoot();
        this.layout.prefWidthProperty().bind(this.widthProperty());
        this.layout.prefHeightProperty().bind(this.heightProperty());
        this.stavitel = new StavitelObsahuOkna(prostrednik);
        this.prostrednik = prostrednik;

    }

    private void setObsah(Parent obsah) {
        this.layout.setCenter(obsah);
    }
    
    private void hetObsah() {
        this.layout.getCenter();
    }

    @Override
    public void prepniSe(int idPohled) {
        Platform.runLater(() -> {
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
                    System.out.println("hra cekani preppni");
                    this.setObsah(stavitel.getHraCekani());
                     System.out.println("hra cekani preppni konec");
                    break;
                case IPohled.HRA_OTAZKA:
                    System.err.println("hra otazka preppni");
                    this.setObsah(stavitel.getHraOtazka());
                     System.err.println("hra otazka preppni konec");
                    break;
                case IPohled.HRA_VYHODNOCENI:
                     this.setObsah(stavitel.getHraVyhodnoceni());
                    break;

                 default:
                    System.err.println("Neznáme id pohledu: " + idPohled);
                    break;
            }
        });
    }
}
