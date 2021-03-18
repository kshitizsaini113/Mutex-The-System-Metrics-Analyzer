pipeline {
    agent any
    
    environment {
        dockerImage = ''
        registry = "kshitizsaini113/mutex"
        registryCredential = 'dockerHub'
    }
    
    stages {

        stage("Build the project"){
            steps{
            sh 'c++ ./src/test.cpp -o testFile.output'
            }
        }

        stage("Testing the output"){
            steps{
            sh './testFile.output'
            }
        }

        stage("Building Docker Image") {
            steps {
                script {
                    dockerImage = docker.build registry
                }
            }
        }
        
        stage("Uploading image to DockerHub") {
            steps {
                script {
                    docker.withRegistry("", registryCredential){
                        dockerImage.push()
                    }
                }
            }
        }
        
    }
}