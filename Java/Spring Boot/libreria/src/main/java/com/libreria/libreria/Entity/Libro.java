package com.libreria.libreria.Entity;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.ManyToOne;
import javax.validation.Valid;

@Entity
public class Libro {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;
    private String titolo;

    @ManyToOne
    @Valid
    private Autore autore;

    public Libro() {
    }

    public Libro(Long id, String titolo, Autore autore) {
        this.id = id;
        this.titolo = titolo;
        this.autore = autore;
    }

    public Long getId() {
        return this.id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getTitolo() {
        return this.titolo;
    }

    public void setTitolo(String titolo) {
        this.titolo = titolo;
    }

    public Autore getAutore() {
        return this.autore;
    }

    public void setAutore(Autore autore) {
        this.autore = autore;
    }

    @Override
    public String toString() {
        return "{" +
            " id='" + getId() + "'" +
            ", titolo='" + getTitolo() + "'" +
            ", autore='" + getAutore() + "'" +
            "}";
    }
}