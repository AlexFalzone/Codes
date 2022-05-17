package com.dmi.dmi.Repository;

import com.dmi.dmi.Entity.Materia;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;
//import com.dmi.dmi.Entity.Materia;

@Repository
public interface MateriaRepository extends JpaRepository<Materia, Long>{}