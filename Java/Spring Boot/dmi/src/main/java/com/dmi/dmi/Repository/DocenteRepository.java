package com.dmi.dmi.Repository;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;
import com.dmi.dmi.Entity.Docente;

@Repository
public interface DocenteRepository extends JpaRepository<Docente, Long>{}