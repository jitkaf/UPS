/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package logika;

import java.io.PrintStream;
import komunikace.TcpOdesilac;
import komunikace.TcpPrijmac;
import uzivatelskeRozhrani.IPohled;

/**
 *
 * @author jitka
 */
public class ProstrednikPoslat {

    private int cekajData = 5;
    private String data = "";
    private int zamekData = 0;
    private int stavStavovehoDiagramu = -1;
    protected IPohled pohled;
    private String otazka="";
    private String acko="";
    private String becko="";
    private String cecko="";
    private int vysledek=0;
    
    public TcpPrijmac tcpPrijimac;
    public TcpOdesilac tcpOdesilac;

    public ProstrednikPoslat(){
        this(null);
    }
    
    public ProstrednikPoslat(IPohled pohled) {
        System.out.println("nastavuji i pohled " + pohled)   ;
        this.setPohled(pohled);
    }
    
    public void setPohled(IPohled pohled){
        this.pohled = pohled;
    }

    public IPohled getPohled() {
        return pohled;
    }

    public void setStavStavovehoDiagramu(int stav) {
        stavStavovehoDiagramu = stav;
    }

    public int getStavStavovehoDiagramu() {
        return stavStavovehoDiagramu;
    }

    public int getCekajData() {
        if (cekajData == 1) {
            System.out.println("jej");
        } else {
            //  System.out.println("--");
        }
        return cekajData;
    }

    public void setCekajData(int bool) {
        System.out.println("nastavuji na " + bool);
        cekajData = bool;
        System.out.println("nastavuji na " + cekajData);
    }

    public String getData() {
        return data;
    }

    public void setData(String data) {
        this.data = data;
    }

    public int getZamekData() {

        return zamekData;
    }

    public void setZamekData(int zamek) {
        zamekData = zamek;
    }

    public void setOtazka(String otazka){
        this.otazka=otazka;
    }
    
    public String getOtazka(){
        return otazka;
    }
    
    public void setAcko(String acko){
        this.acko=acko;
    }
    
    public String getAcko(){
        return acko;
    }
    
    public void setBecko(String becko){
        this.becko = becko;
    }
    
    public String getBecko(){
        return becko;
    }
    
    public void setCecko(String cecko){
        this.cecko= cecko;
    }
    
    public String getCecko(){
        return cecko;
    }
    
    public void setVysledek(int vysledek){
        this.vysledek = vysledek;
    }
    
    public int getVysledek(){
        return vysledek;
    }
}
