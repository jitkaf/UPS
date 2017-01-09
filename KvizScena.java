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
            switch (idPohled) {
                case IPohled.PRIHLASENI:
                    this.setObsah(stavitel.getPrihlasovatko());
                    break;
                //case IPohled.HERNI_MISTNOSTI: this.layout.setCenter(...); break;
                //  case IPohled.KONEC_HRY: this.layout.setCenter(...); break;
                default:
                    System.err.println("Nezname id pohledu: " + idPohled);
                    break;
            }
        });
    }
}
