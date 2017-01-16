/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package uzivatelskeRozhrani;

/**
 *
 * @author jitka
 */
public interface IPohled {
 /* public static final int VYBER_SERVERU = 1;
  public static final int HERNI_MISTNOSTI = 2;
  public static final int KONEC_HRY = 3;*/
  
    
  public static final int PRIPOJENI = 0;
  public static final int PRIPOJENI_ZNOVU = -1;
  public static final int PRIPOJENI_CHYBA_PORTU = -2;
  public static final int PRIPOJENI_CHYBA = -3;
  public static final int PRIHLASENI = 1;
  public static final int PRIHLASENI_DUPLICITA =13;
  public static final int PRIHLASENI_JMENO =11;
  public static final int PRIHLASENI_HESLO =12;
  public static final int START = 2;
  public static final int HRA_CEKANI = 4;
  public static final int HRA_OTAZKA = 3;
  public static final int HRA_VYHODNOCENI = 5;

  
  public void prepniSe(int idPohled);
}
