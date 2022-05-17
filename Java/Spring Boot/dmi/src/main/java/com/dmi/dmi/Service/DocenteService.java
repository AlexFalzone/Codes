package com.dmi.dmi.Service;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import com.dmi.dmi.Repository.DocenteRepository;
import com.dmi.dmi.Entity.Docente;

@Service
public class DocenteService {

    @Autowired
    private DocenteRepository repository;

    public Docente addDocente(Docente e) {
        return repository.save(e);
    }

    public Optional<Docente> getDocente(Long id) {
        return repository.findById(id);
    }

    public List<Docente> getAllDocentes() {
        List<Docente> output = new ArrayList<Docente>();
        repository.findAll().forEach(output::add);
        return output;
    }

    public Docente updateDocente(Docente e) {
        return repository.save(e);
    }

    public void deleteDocente(Docente e) {
        repository.delete(e);
}

    public void deleteDocente(Long id) {
        repository.deleteById(id);
    }
}