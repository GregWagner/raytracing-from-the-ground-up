// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 18.5(a)

void 												
World::build(void) {
	int num_samples = 100;   
	
	Sampler* sampler_ptr = new MultiJittered(num_samples);

	vp.set_hres(600);
	vp.set_vres(600);
	vp.set_max_depth(0);
	vp.set_sampler(sampler_ptr);	

	background_color = RGBColour(0.5);

	tracer_ptr = new AreaLighting(this);

	Pinhole* camera = new Pinhole;
	camera->set_eye(-20, 10, 20);
	camera->set_lookat(0, 2, 0); 	
	camera->set_view_distance(1080);          
	camera->compute_uvw();     
	set_camera(camera); 

	
	Emissive* emissive_ptr = new Emissive;
	emissive_ptr->scale_radiance(40.0);
	emissive_ptr->set_ce(white);
	
	
	// disk for the disk light
	
	Point3D center(0.0, 7.0, -7.0);
	float width = 4.0;
	float radius = 0.56 * width;
	Normal normal(0, 0, 1);
		
	
	Disk* disk_ptr = new Disk(center, normal, radius);
	disk_ptr->set_material(emissive_ptr);
	disk_ptr->set_sampler(sampler_ptr);
	disk_ptr->set_shadows(false);
	disk_ptr->compute_uvw();
	add_object(disk_ptr);
	
		
	AreaLight* area_light_ptr = new AreaLight;
	area_light_ptr->set_object(disk_ptr);
	area_light_ptr->set_shadows(true);
	add_light(area_light_ptr);
	
	
	// Four axis aligned boxes
		
	float box_width 	= 1.0; 		// x dimension
	float box_depth 	= 1.0; 		// z dimension
	float box_height 	= 4.5; 		// y dimension
	float gap			= 3.0; 
	
	Matte* matte_ptr1 = new Matte;			
	matte_ptr1->set_ka(0.25); 
	matte_ptr1->set_kd(0.75);
	matte_ptr1->set_cd(0.4, 0.7, 0.4);     // green
	
	Box* box_ptr0 = new Box(Point3D(- 1.5 * gap - 2.0 * box_width, 0.0, -0.5 * box_depth), 
							Point3D(-1.5 * gap  - box_width, box_height, 0.5 * box_depth)); 
	box_ptr0->set_material(matte_ptr1);
	add_object(box_ptr0);
	
	Box* box_ptr1 = new Box(Point3D(- 0.5 * gap - box_width, 0.0, -0.5 * box_depth), 
							Point3D(-0.5 * gap, box_height, 0.5 * box_depth)); 
	box_ptr1->set_material(matte_ptr1);
	add_object(box_ptr1);
		
	Box* box_ptr2 = new Box(Point3D(0.5 * gap, 0.0, -0.5 * box_depth), 
							Point3D(0.5 * gap + box_width, box_height, 0.5 * box_depth));
	box_ptr2->set_material(matte_ptr1);
	add_object(box_ptr2);
	
	Box* box_ptr3 = new Box(Point3D(1.5 * gap + box_width, 0.0, -0.5 * box_depth), 
							Point3D(1.5 * gap + 2.0 * box_width, box_height, 0.5 * box_depth));
	box_ptr3->set_material(matte_ptr1);
	add_object(box_ptr3);

		
	// ground plane
	
	Matte* matte_ptr2 = new Matte;			
	matte_ptr2->set_ka(0.1); 
	matte_ptr2->set_kd(0.90);
	matte_ptr2->set_cd(white);
		
	Plane* plane_ptr = new Plane(Point3D(0.0), Normal(0, 1, 0)); 
	plane_ptr->set_material(matte_ptr2);
	add_object(plane_ptr);	
}


