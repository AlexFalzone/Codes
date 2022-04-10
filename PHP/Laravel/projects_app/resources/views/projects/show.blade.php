@extends('layout')

@section('content')
    <h1>Project {{$project->id}}</h1>
    <b>Title:</b> {{$project->title}}<br>
    <b>Description:</b> {{$project->description}}<br>
    @if ($project->tasks->count())
        <b>Tasks:</b>
        <ul>
            @foreach ($project->tasks as $task)
                <li>
                    <a href="/tasks/{{$task->id}}">{{$task->title}}</a>
                </li>
            @endforeach
        </ul>
    @endif
    <br>
    <form action="/projects/{{$project->id}}/edit" method="get">
        <input type="submit" value="Edit/Delete project"><br><br>
    </form>
    <form action="/tasks/create" method="post">
        @csrf
        <input type="hidden" name="project_id" id="project_id" value="{{$project->id}}">
        <input type="submit" value="Create task">
    </form>
@endsection