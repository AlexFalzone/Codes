package com.dmi.dmi.Entity;

import javax.persistence.CascadeType;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.OneToOne;

@Entity
public class Materia {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;
    private String nome;
    private String cfu;

    @OneToOne(cascade = CascadeType.ALL)
    @JoinColumn(name = "docente_id", referencedColumnName = "id")
    private Docente docente;

    public Materia() {
    }

    public Materia(String nome, String cfu, Docente docente) {
        this.nome = nome;
        this.cfu = cfu;
        this.docente = docente;
    }
    
    public Long getId() {
        return this.id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getNome() {
        return this.nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public String getCfu() {
        return this.cfu;
    }

    public void setCfu(String cfu) {
        this.cfu = cfu;
    }

    public Docente getDocente() {
        return this.docente;
    }

    public void setDocente(Docente docente) {
        this.docente = docente;
    }
    
    @Override
    public String toString() {
        return "{" +
            " id='" + getId() + "'" +
            ", nome='" + getNome() + "'" +
            ", cfu='" + getCfu() + "'" +
            ", docente='" + getDocente() + "'" +
            "}";
    }

}