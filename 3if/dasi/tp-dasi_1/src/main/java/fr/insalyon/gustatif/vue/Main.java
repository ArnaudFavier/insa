package fr.insalyon.gustatif.vue;

import fr.insalyon.gustatif.dao.ClientDao;
import fr.insalyon.gustatif.dao.JpaUtil;
import fr.insalyon.gustatif.dao.ProduitDao;
import fr.insalyon.gustatif.dao.RestaurantDao;
import fr.insalyon.gustatif.metier.modele.Client;
import fr.insalyon.gustatif.metier.modele.Produit;
import fr.insalyon.gustatif.metier.modele.Restaurant;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author afavier
 */
public class Main {

    public static void main(String[] args) {

        ClientDao clientDao = new ClientDao();
        ProduitDao produitDao = new ProduitDao();
        RestaurantDao restaurantDao = new RestaurantDao();

        JpaUtil.creerEntityManager();

        JpaUtil.ouvrirTransaction();
        Client client1 = new Client("Robert", "Michel", "42 rue du Code", "rob.mich@code.com");
        Client client2 = new Client("Jack", "Sparrow", "42 rue du Pirate", "jack@blackpearl.com");

        Produit produit1 = new Produit("cafee", "De la bonne chicore", 12.0f, 100.0f);
        Produit produit2 = new Produit("bonbon", "Des bonbons colores", 18.0f, 280.0f);

        Restaurant restaurant1 = new Restaurant("Le petit coin", "Calme et tranquill,e el petit coin vous accueille", "Rue de la tranquilité");
        Restaurant restaurant2 = new Restaurant("Pirate island", "Yoo my old mate ! Viens rencontrer barbe bleu !", "Bateau de la guerre");
        try {
            /*clientDao.create(client1);
             clientDao.create(client2);

             produitDao.create(produit1);
             produitDao.create(produit2);

             restaurantDao.create(restaurant1);
             restaurantDao.create(restaurant2);*/
        } catch (Throwable ex) {
            Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
        }
        JpaUtil.validerTransaction();

        try {
            System.out.println(clientDao.findAll());
            System.out.println(produitDao.findAll());
            System.out.println(restaurantDao.findAll());
        } catch (Throwable ex) {
            Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
        }

        JpaUtil.fermerEntityManager();

    }
}
