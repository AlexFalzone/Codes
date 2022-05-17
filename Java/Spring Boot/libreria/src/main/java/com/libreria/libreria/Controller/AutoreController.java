package com.libreria.libreria.Controller;

import java.net.URI;
import java.net.URISyntaxException;
import java.util.List;
import java.util.Optional;

import javax.validation.Valid;

import com.libreria.libreria.Entity.Autore;
import com.libreria.libreria.Service.AutoreService;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.DeleteMapping;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.PutMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/api")
public class AutoreController {

    @Autowired
    private AutoreService service;

    @GetMapping("/autori")
    public ResponseEntity<List<Autore>> getAllAutores() {
        List<Autore> entityList = service.getAllAutores();
        return ResponseEntity.ok(entityList);
    }

    @GetMapping("/autore/{id}")
    public ResponseEntity<Autore> getAutore(@PathVariable long id) {
        Optional<Autore> entity = service.getAutore(id);
        if(entity.isPresent())
            return ResponseEntity.ok(entity.get());
        else
            return ResponseEntity.notFound().build();
    }

    @PostMapping("/autore")
    public ResponseEntity<Autore> addAutore(@Valid @RequestBody Autore e) throws URISyntaxException {
        if (e.getId() != null) {
            return ResponseEntity.badRequest().build();
        }
        Autore entity = service.addAutore(e);
        return ResponseEntity.created(new URI("/resourceRootPath/resourcePath" + entity.getId())).body(entity);
    }

    @PutMapping("/autore")
    public ResponseEntity<Autore> updateAutore(@Valid @RequestBody Autore e) {
        if (e.getId() == null)
            return ResponseEntity.notFound().build();
        Autore entity = service.updateAutore(e);
        return ResponseEntity.ok(entity);
    }

    @DeleteMapping("/autore/{id}")
    public ResponseEntity<Void> deleteAutore(@PathVariable long id) {
        if (service.getAutore(id).isEmpty())
            return ResponseEntity.notFound().build();

        service.deleteAutore(id);
        return ResponseEntity.ok().build();
    }
}