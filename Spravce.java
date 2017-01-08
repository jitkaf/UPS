/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package uzivatelskeRozhrani;

import logika.ProstrednikPoslat;

/**
 *
 * @author jitka
 */
public class Spravce extends Thread{
    ProstrednikPoslat prostrednikPos;
    public Spravce(ProstrednikPoslat prostrednikPos){
        this.prostrednikPos=prostrednikPos;
    }
    
         @Override
	 public void run(){
             Okno.launch(Okno.class, prostrednikPos);
        //     Okno.launch(Okno.class); 
         }
}
