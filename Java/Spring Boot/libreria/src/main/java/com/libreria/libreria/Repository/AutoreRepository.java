package com.libreria.libreria.Repository;

import com.libreria.libreria.Entity.Autore;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;
@Repository
public interface AutoreRepository extends JpaRepository<Autore, Long>{}