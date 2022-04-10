@extends('layout')

@section('content')
    <h1>Edit/Delete task {{$task->id}}</h1>
    <form action="/tasks/{{$task->id}}" method="post">
        @csrf
        @method('PATCH')
        <label for="title">Title</label> <br>
        <input type="text" name="title" id="title" value="{{$task->title}}"><br><br>
        <label for="description">Description</label> <br>
        <textarea name="description" id="description" cols="30" rows="10">{{$task->description}}</textarea><br><br>
        <label for="project_id">Project ID</label> <br>
        <input type="number" name="project_id" id="project_id" value="{{$task->project_id}}"><br><br>
        <input type="submit" value="Save task {{$task->id}} as above"><br><br>
    </form>
    <form action="/tasks/{{$task->id}}" method="post">
        @csrf
        @method('DELETE')
        <input type="submit" value="Delete task {{$task->id}}">
    </form>
@endsection