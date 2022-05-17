package com.match.match.Controller;

import java.net.URI;
import java.net.URISyntaxException;
import java.util.List;
import java.util.Optional;

import javax.validation.Valid;

import com.match.match.Entity.Team;
import com.match.match.Service.TeamService;

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
public class TeamController {

    @Autowired
    private TeamService service;

    @GetMapping("/team")
    public ResponseEntity<List<Team>> getAllTeams() {
        List<Team> entityList = service.getAllTeams();
        return ResponseEntity.ok(entityList);
    }

    @GetMapping("/team/{id}")
    public ResponseEntity<Team> getTeam(@PathVariable long id) {
        Optional<Team> entity = service.getTeam(id);
        if(entity.isPresent())
            return ResponseEntity.ok(entity.get());
        else
            return ResponseEntity.notFound().build();
    }

    @PostMapping("/team")
    public ResponseEntity<Team> addTeam(@Valid @RequestBody Team e) throws URISyntaxException {
        if (e.getId() != null) {
            return ResponseEntity.badRequest().build();
        }
        Team entity = service.addTeam(e);
        return ResponseEntity.created(new URI("/api/resourcePath" + entity.getId())).body(entity);
    }

    @PutMapping("/team")
    public ResponseEntity<Team> updateTeam(@Valid @RequestBody Team e) {
        if (e.getId() == null)
            return ResponseEntity.notFound().build();
        Team entity = service.updateTeam(e);
        return ResponseEntity.ok(entity);
    }

    @DeleteMapping("/team/{id}")
    public ResponseEntity<Void> deleteTeam(@PathVariable long id) {
        if (service.getTeam(id).isEmpty())
            return ResponseEntity.notFound().build();

        service.deleteTeam(id);
        return ResponseEntity.ok().build();
    }
}