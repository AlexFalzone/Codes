package com.libreria.libreria.Service;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

import com.libreria.libreria.Entity.Libro;
import com.libreria.libreria.Repository.LibroRepository;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class LibroService {

    @Autowired
    private LibroRepository repository;

    public Libro addLibro(Libro e) {
        return repository.save(e);
    }

    public Optional<Libro> getLibro(Long id) {
        return repository.findById(id);
    }

    public List<Libro> getAllLibros() {
        List<Libro> output = new ArrayList<Libro>();
        repository.findAll().forEach(output::add);
        return output;
    }

    public Libro updateLibro(Libro e) {
        return repository.save(e);
    }

    public void deleteLibro(Libro e) {
        repository.delete(e);
}

    public void deleteLibro(Long id) {
        repository.deleteById(id);
    }
}