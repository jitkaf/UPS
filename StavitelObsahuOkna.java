package uzivatelskeRozhrani;

import java.io.IOException;
import java.net.Socket;
import uzivatelskeRozhrani.obsahyOkna.Start;
import uzivatelskeRozhrani.obsahyOkna.Prihlasovatko;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.event.ActionEvent;

import javafx.scene.control.CheckBox;
import javafx.scene.control.Label;
import javafx.scene.control.RadioButton;
import javafx.scene.control.Spinner;
import javafx.scene.control.TextArea;
import javafx.scene.control.Toggle;
import javafx.scene.control.ToggleGroup;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.VBox;
import komunikace.TcpOdesilac;
import komunikace.TcpPrijmac;
import data.Prostrednik;
import uzivatelskeRozhrani.obsahyOkna.HraCekani;
import uzivatelskeRozhrani.obsahyOkna.HraOtazka;
import uzivatelskeRozhrani.obsahyOkna.HraVyhodnoceni;
import uzivatelskeRozhrani.obsahyOkna.Pripojovatko;

public class StavitelObsahuOkna {

    private Prostrednik prostrednikPos;

    private BorderPane okno; //tohle budu predavat

    int scena = 0;

    private TextArea vstup = new TextArea();
    private TextArea vystup = new TextArea();
    private TextArea posunl = new TextArea();
    private TextArea posuns = new TextArea();
    Spinner posun, posun2;
    private TextArea klic;
    private CheckBox auto;
    private int indexSifry = 0;
    private BorderPane layout;
    private int od = 0;

    public StavitelObsahuOkna(Prostrednik prostrednikPos) {
        this.prostrednikPos = prostrednikPos;
    }

    public int getScena() {
        return scena;
    }

    public Pripojovatko getPripojovatko(int vysledek) {
        Pripojovatko pripojovatko = new Pripojovatko(vysledek);

        pripojovatko.konec.setOnAction((ActionEvent event) -> {
            setAkceUkoncit();

        });

        pripojovatko.pripoj.setOnAction((ActionEvent event) -> {
            System.out.println("Připojeni aplikace.");
            String ip = pripojovatko.getIpText();
            String port = pripojovatko.getPortText();
          //  System.out.println("ip je " + ip + " port je " + port);
            int portCislo = stringToInt(port);
            if ((portCislo > 65535) || (portCislo < 0)) {
                prostrednikPos.getPohled().prepniSe(IPohled.PRIPOJENI_CHYBA_PORTU);
                System.out.println("Port musí být číslo od 0 do 65535!");
            } else {

                try {
                    Socket socket = new Socket(ip, portCislo);
                    System.out.print("Pripojeno na : " + socket.getInetAddress().toString());
                    prostrednikPos.tcpOdesilac = new TcpOdesilac(socket, 30, prostrednikPos);
                    prostrednikPos.tcpPrijimac = new TcpPrijmac(socket, 30, prostrednikPos);
                    prostrednikPos.tcpOdesilac.setDaemon(true);
                    prostrednikPos.tcpPrijimac.setDaemon(true);
                    prostrednikPos.tcpOdesilac.start();
                    prostrednikPos.tcpPrijimac.start();
                    prostrednikPos.getPohled().prepniSe(IPohled.PRIHLASENI);
                } catch (IOException ex) {
                    System.err.println("Pripojeni selhalo, zadejte prosim IP adresu a port lépe.");
                    prostrednikPos.getPohled().prepniSe(IPohled.PRIPOJENI_CHYBA);
                    return;
                }

            }

        });

        return pripojovatko;
    }

    public Prihlasovatko getPrihlasovatko(int opakovani) {
        Prihlasovatko prihlasovatko = new Prihlasovatko(opakovani);

        prihlasovatko.registrovat.setOnAction((ActionEvent event) -> {
            setAkcePrihlaseni("0|", prihlasovatko);
        });

        prihlasovatko.prihlasit.setOnAction((ActionEvent event) -> {
            String jmeno = prihlasovatko.getJmeno();
            String heslo = prihlasovatko.getHeslo();
            setAkcePrihlaseni("1|", prihlasovatko);
        });

        prihlasovatko.konec.setOnAction((ActionEvent event) -> {
            setAkceUkoncit();

        });

        return prihlasovatko;
    }

    public Start getStart() {
        Start start = new Start();

        start.startuj.setOnAction((ActionEvent event) -> {
            setAkceStart();

        });

        start.odhlasit.setOnAction((ActionEvent event) -> {
            setAkceOdhlasit();

        });

        start.ukoncit.setOnAction((ActionEvent event) -> {
            setAkceUkoncit();

        });

        return start;
    }

    public HraCekani getHraCekani() {
        HraCekani hraCekani = new HraCekani();

        hraCekani.ukoncit.setOnAction((ActionEvent event) -> {
            setAkceUkoncit();

        });

        hraCekani.odhlasit.setOnAction((ActionEvent event) -> {
            setAkceOdhlasit();
        });
        return hraCekani;
    }

    public HraOtazka getHraOtazka() {
        String otazka = prostrednikPos.getOtazka();
        String a = prostrednikPos.getAcko();
        String b = prostrednikPos.getBecko();
        String c = prostrednikPos.getCecko();
        HraOtazka hraOtazka = new HraOtazka(otazka, a, b, c);

        hraOtazka.toggleGroupTG.selectedToggleProperty().addListener(new ChangeListener<Toggle>() {
            @Override
            public void changed(ObservableValue<? extends Toggle> ov, Toggle t, Toggle t1) {

                RadioButton chk = (RadioButton) t1.getToggleGroup().getSelectedToggle(); // Cast object to radio button

                if (chk.getText().charAt(0) == 'A') {
                    od = 1;
                } else if (chk.getText().charAt(0) == 'B') {
                    od = 2;
                } else if (chk.getText().charAt(0) == 'C') {
                    od = 3;
                }
            }
        });

        hraOtazka.odpovedet.setOnAction((ActionEvent event) -> {
            if (prostrednikPos.getZamekData() == 0) {
                prostrednikPos.setZamekData(1);
                prostrednikPos.setData("3|" + od);
                prostrednikPos.setZamekData(2);
                prostrednikPos.getPohled().prepniSe(IPohled.HRA_CEKANI);
            } else {
                System.out.println("HraOtazka obsazeno");
            }

        });

        hraOtazka.odhlasit.setOnAction((ActionEvent event) -> {
            setAkceOdhlasit();

        });

        hraOtazka.ukoncit.setOnAction((ActionEvent event) -> {
            setAkceUkoncit();

        });

        return hraOtazka;
    }

    public HraVyhodnoceni getHraVyhodnoceni() {
        int vyhodnoceni = prostrednikPos.getVysledek();
        System.out.println("Jsem v Stavitel obsahu getHraVyhodnoceni a vysledek je " + vyhodnoceni);
        HraVyhodnoceni hraVyhodnoceni = new HraVyhodnoceni(vyhodnoceni);

        hraVyhodnoceni.odhlasit.setOnAction((ActionEvent event) -> {
            setAkceOdhlasit();

        });

        hraVyhodnoceni.ukoncit.setOnAction((ActionEvent event) -> {
            setAkceUkoncit();

        });

        hraVyhodnoceni.start.setOnAction((ActionEvent event) -> {
            setAkceStart();

        });

        return hraVyhodnoceni;
    }

    private static int stringToInt(String param) {
        try {
            return Integer.valueOf(param);
        } catch (NumberFormatException e) {
            return -1;
        }
    }

    private String odPajpuj(String s) {
        String[] p = s.split("\\|");

        int delka = p.length;
        System.out.println("s  " + s + " delka" + delka);
        String navrat = "";
        for (int i = 0; i < delka; i++) {

            navrat = navrat + p[i];
            System.out.println(navrat);
        }
        return navrat;
    }

    private void setAkceOdhlasit() {
        if (prostrednikPos.getZamekData() == 0) {
            prostrednikPos.setZamekData(1);
            prostrednikPos.setData("4|1");
            prostrednikPos.setZamekData(2);
            prostrednikPos.getPohled().prepniSe(IPohled.PRIHLASENI);
        } else {
            System.out.println("HraCekani obsazeno");
        }

        //   System.exit(0);
    }

    private void setAkceUkoncit() {
        System.out.println("Ukonceni aplikace.");
        if (prostrednikPos.getZamekData() == 0) {
            prostrednikPos.setZamekData(1);
            prostrednikPos.setData("4|0");
            prostrednikPos.setZamekData(2);

        } else {
            System.out.println("zamčeno " + prostrednikPos.getZamekData());
        }
        // System.exit(0);
    }

    private void setAkceStart() {
        if (prostrednikPos.getZamekData() == 0) {
            prostrednikPos.setZamekData(1);
            prostrednikPos.setData("2");
            prostrednikPos.setZamekData(2);
            prostrednikPos.getPohled().prepniSe(IPohled.HRA_CEKANI);
        } else {
            System.out.println("start obsazeno");
        }
    }

    private void setAkcePrihlaseni(String s, Prihlasovatko prihlasovatko) {

        String jmeno = prihlasovatko.getJmeno();
        String heslo = prihlasovatko.getHeslo();
        //vyber sifrovaci metody podle zvoleneho radiobuttonu
        jmeno = odPajpuj(jmeno);
        heslo = odPajpuj(heslo);
        // if ((jmeno.length() != 0) && (heslo.length() != 0)) {
        //zde doplnit zamek lepe
        if (prostrednikPos.getZamekData() == 0) {
            prostrednikPos.setZamekData(1);
            System.out.println("chci poslat: " + s + jmeno + s + heslo);
            prostrednikPos.setData(s + jmeno + "|" + heslo);
            //  prostrednikPos.setCekajData(1);
            prostrednikPos.setZamekData(2);

            prihlasovatko.setVysledek("Čeká se na vyhodnocení" + prostrednikPos.getCekajData());

        } else {
            System.out.println("zamčeno " + prostrednikPos.getZamekData());
        }

    }

}
