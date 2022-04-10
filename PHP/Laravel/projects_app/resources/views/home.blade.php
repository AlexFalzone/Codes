@extends('layout')

@section('content')
    <h1>Projects operations</h1>

    <form action="/projects/create" method="get">
        <input type="submit" value="Create project"><br><br><br>
    </form>
    
    <form action="/projects" method="get">
        <input type="submit" value="Show all projects"><br><br><br>
    </form>

    <form action="/projects/help_show" method="post">
        @csrf
        <label for="id">Project ID </label><br>
        <input type="number" name="id" id="id"><br><br>
        <input type="submit" value="Search project"><br><br><br>
    </form>

    <form action="/projects" method="post">
        @csrf
        @method('DELETE')
        <input type="submit" value="Delete all projects"><br><br><br>
    </form>

    <h1>Task operations</h1>

    <form action="/tasks/create" method="get">
        <input type="submit" value="Create task"><br><br><br>
    </form>

    <form action="/tasks" method="get">
        <input type="submit" value="Show all tasks"><br><br><br>
    </form>

    <form action="/tasks/help_show" method="post">
        @csrf
        <label for="id">Task ID </label><br>
        <input type="number" name="id" id="id"><br><br>
        <input type="submit" value="Search task"><br><br><br>
    </form>

    <form action="/tasks" method="post">
        @csrf
        @method('DELETE')
        <input type="submit" value="Delete all tasks"><br><br><br>
    </form>
@endsection




