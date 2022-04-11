package com.libreria.libreria.Service;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

import com.libreria.libreria.Entity.Autore;
import com.libreria.libreria.Repository.AutoreRepository;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class AutoreService {

    @Autowired
    private AutoreRepository repository;

    public Autore addAutore(Autore e) {
        return repository.save(e);
    }

    public Optional<Autore> getAutore(Long id) {
        return repository.findById(id);
    }

    public List<Autore> getAllAutores() {
        List<Autore> output = new ArrayList<Autore>();
        repository.findAll().forEach(output::add);
        return output;
    }

    public Autore updateAutore(Autore e) {
        return repository.save(e);
    }

    public void deleteAutore(Autore e) {
        repository.delete(e);
}

    public void deleteAutore(Long id) {
        repository.deleteById(id);
    }
}
