package fr.insalyon.gustatif.metier.modele;

import com.google.maps.model.LatLng;
import java.io.Serializable;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.Id;

@Entity
public class Client implements Serializable {

    @Id @GeneratedValue
    private Long id;
    private String nom;
    private String prenom;
    private String mail;
    private String motDePasse;
    private String adresse;
    private Double longitude;
    private Double latitude;

    public Client() {
    }

    public Client(String nom, String prenom, String mail, String motDePasse, String adresse) {
        this.nom = nom;
        this.prenom = prenom;
        this.mail = mail;
        this.motDePasse = motDePasse;
        this.adresse = adresse;
    }

    public Long getId() {
        return id;
    }

    public String getNom() {
        return nom;
    }

    public String getPrenom() {
        return prenom;
    }

    public String getMail() {
        return mail;
    }

    public String getMotDePasse() {
        return motDePasse;
    }

    public String getAdresse() {
        return adresse;
    }

    public Double getLongitude() {
        return longitude;
    }

    public Double getLatitude() {
        return latitude;
    }

    public void setNom(String nom) {
        this.nom = nom;
    }

    public void setPrenom(String prenom) {
        this.prenom = prenom;
    }

    public void setMail(String mail) {
        this.mail = mail;
    }

    public void setMotDePasse(String motDePasse) {
        this.motDePasse = motDePasse;
    }

    public void setAdresse(String adresse) {
        this.adresse = adresse;
    }

    public void setCoordonnees(LatLng latLng) {
        this.longitude = latLng.lng;
        this.latitude = latLng.lat;
    }

    @Override
    public String toString() {
        return "Client{" +
                "id=" + id +
                ", nom=" + nom +
                ", prenom=" + prenom +
                ", mail=" + mail +
                ", motDePasse=" + motDePasse +
                ", adresse=" + adresse +
                ", longitude=" + longitude +
                ", latitude=" + latitude +
                '}';
    }

}
