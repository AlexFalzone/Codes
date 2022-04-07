package com.dmi.dmi.Service;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

import com.dmi.dmi.Repository.MateriaRepository;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import com.dmi.dmi.Entity.Materia;

@Service
public class MateriaService {

    @Autowired
    private MateriaRepository repository;

    public Materia addMateria(Materia e) {
        return repository.save(e);
    }

    public Optional<Materia> getMateria(Long id) {
        return repository.findById(id);
    }

    public List<Materia> getAllMaterias() {
        List<Materia> output = new ArrayList<Materia>();
        repository.findAll().forEach(output::add);
        return output;
    }

    public Materia updateMateria(Materia e) {
        return repository.save(e);
    }

    public void deleteMateria(Materia e) {
        repository.delete(e);
}

    public void deleteMateria(Long id) {
        repository.deleteById(id);
    }
}