package com.libreria.libreria.Controller;

import java.net.URI;
import java.net.URISyntaxException;
import java.util.List;
import java.util.Optional;

import javax.validation.Valid;

import com.libreria.libreria.Entity.Libro;
import com.libreria.libreria.Service.LibroService;

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
public class LibroController {

    @Autowired
    private LibroService service;

    @GetMapping("/libri")
    public ResponseEntity<List<Libro>> getAllLibros() {
        List<Libro> entityList = service.getAllLibros();
        return ResponseEntity.ok(entityList);
    }

    @GetMapping("/libro/{id}")
    public ResponseEntity<Libro> getLibro(@PathVariable long id) {
        Optional<Libro> entity = service.getLibro(id);
        if(entity.isPresent())
            return ResponseEntity.ok(entity.get());
        else
            return ResponseEntity.notFound().build();
    }

    @PostMapping("/libro")
    public ResponseEntity<Libro> addLibro(@Valid @RequestBody Libro e) throws URISyntaxException {
        if (e.getId() != null) {
            return ResponseEntity.badRequest().build();
        }
        Libro entity = service.addLibro(e);
        return ResponseEntity.created(new URI("/resourceRootPath/resourcePath" + entity.getId())).body(entity);
    }

    @PutMapping("/libro")
    public ResponseEntity<Libro> updateLibro(@Valid @RequestBody Libro e) {
        if (e.getId() == null)
            return ResponseEntity.notFound().build();
        Libro entity = service.updateLibro(e);
        return ResponseEntity.ok(entity);
    }

    @DeleteMapping("/libro/{id}")
    public ResponseEntity<Void> deleteLibro(@PathVariable long id) {
        if (service.getLibro(id).isEmpty())
            return ResponseEntity.notFound().build();

        service.deleteLibro(id);
        return ResponseEntity.ok().build();
    }
}