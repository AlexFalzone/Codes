package com.libreria.libreria.Repository;

import com.libreria.libreria.Entity.Libro;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;
@Repository
public interface LibroRepository extends JpaRepository<Libro, Long>{}